#include <QJsonArray>
#include <QJsonObject>
#include <assert.h>

#include "cartModel.h"
#include "sessionManager.h"

using namespace std::placeholders;

CartModel::CartModel(QObject *parent)
    : QObject(parent),
      showCartsReady_(false),
      stationCartsReady_(false),
      cartWallTypeMap_({ { CartWallType::STATION, stationCarts_ },
                         { CartWallType::SHOW, showCarts_ },
                         { CartWallType::USER, userCarts_ } })
{
    unsigned int showId = SessionManager::getInstance().getShowId();
    QString showIdString = QString::number(showId);

    auto stationProcessor = std::bind(&CartModel::processCartWall, this, _1,
                                      std::ref(stationCarts_),
                                      [=]{stationCartsReady();});

    auto showProcessor = std::bind(&CartModel::processCartWall, this, _1,
                                   std::ref(showCarts_), [=]{showCartsReady();});

    auto errorHandler = std::bind(&CartModel::requestError, this, _1, _2);
}

CartButton *CartModel::getButton(const enum CartWallType &cartWall,
                                 const cartLocus &locus,
                                 AudioManager *audioMan, QWidget *parent) const
{
    assert(isReady());
    const auto &cartWallMap = cartWallTypeMap_.find(cartWall);

    if (cartWallMap == cartWallTypeMap_.end())
        return new CartButton(parent);

    const auto &cart = cartWallMap->second.find(locus);

    if (cart == stationCarts_.end())
        return new CartButton(parent);

    return new CartButton(parent, cart->second.title, "foo", audioMan,
                          cart->second.theme.textColour,
                          cart->second.theme.bgColour);
}

void CartModel::requestError(const QString &errorString,
                             QNetworkReply::NetworkError error) const
{
    QString modelErrorString = "Error getting carts configuration: " + errorString;

    emit modelError(modelErrorString);
}

bool CartModel::isReady() const
{
    return showCartsReady_ && stationCartsReady_;
}

void CartModel::checkReady() const
{
    if (isReady())
        emit modelReady();
}

void CartModel::showCartsReady()
{
    showCartsReady_ = true;

    checkReady();
}

void CartModel::stationCartsReady()
{
    stationCartsReady_ = true;

    checkReady();
}

QColor CartModel::getColourFromHexString(const QString &value) const
{
    QColor ret;

    ret.setNamedColor(value);

    return ret;
}

void CartModel::processCarts(const QJsonDocument &data, cartMap &destMap,
                             std::function<void()> callback)
{
    for (const auto stationCart : data.array()) {
        const auto stationCartObject = stationCart.toObject();
        const auto stationCartTheme = stationCartObject["theme"].toObject();

        struct cartLocus locus;
        struct cartProperties newCart;

        locus.x = stationCartObject["x"].toInt();
        locus.y = stationCartObject["y"].toInt();
        locus.page = stationCartObject["page"].toInt();
        newCart.title = stationCartObject["title"].toString();
        newCart.theme.bgColour =
                getColourFromHexString(stationCartTheme["bg_colour"].toString());
        newCart.theme.textColour =
                getColourFromHexString(stationCartTheme["text_colour"].toString());

        newCart.locus = locus;

        destMap.insert({locus, newCart});
    }

    callback();
}

void CartModel::processCartWall(const QJsonDocument &data, cartMap &destMap,
                                std::function<void ()> callback)
{
    std::list<unsigned int> cartWalls;

    for (const auto cartWall : data.array()) {
        QJsonObject cartWallObject = cartWall.toObject();
        cartWalls.push_back(cartWallObject["id"].toInt());
    }

    // If there are no cart walls, there's nothing we can do.  Call
    // the ready callback and just return.
    if (!cartWalls.size()) {
        callback();
        return;
    }

    QString cartWallId = QString::number(cartWalls.front());

    auto cartProcessCallback = std::bind(&CartModel::processCarts, this,
                                         _1, std::ref(destMap), callback);

    auto errorHandler = std::bind(&CartModel::requestError, this, _1, _2);
}
