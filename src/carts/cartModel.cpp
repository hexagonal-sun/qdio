#include <QSqlQuery>
#include <QSqlError>
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

    QSqlQuery stationCartsQuery;
    stationCartsQuery.prepare("select * from get_station_cartwalls_for_show(:showid)");
    stationCartsQuery.bindValue(":showid", showId);
    processCartWall(stationCartsQuery, stationCarts_, [=]{stationCartsReady();});

    QSqlQuery showCartsQuery;
    showCartsQuery.prepare("select * from get_cartwalls_for_show(:showid)");
    showCartsQuery.bindValue(":showid", showId);
    processCartWall(showCartsQuery, showCarts_, [=]{showCartsReady();});
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

void CartModel::requestError(const QString &errorString) const
{
    QString modelErrorString = "Error getting carts configuration: " + errorString;

    emit modelError(modelErrorString);
}

void CartModel::processCarts(int cartWallId, cartMap &destMap,
                             std::function<void()> callback)
{
    QSqlQuery cartsQuery;
    cartsQuery.prepare("SELECT * from get_carts_for_cartwall(:cartwallid)");
    cartsQuery.bindValue(":cartwallid", cartWallId);

    if (!cartsQuery.exec()) {
        requestError(cartsQuery.lastError().text());
        return;
    }

    while (cartsQuery.next()) {
        struct cartLocus locus;
        struct cartProperties newCart;

        locus.x = cartsQuery.value("x").toInt();
        locus.y = cartsQuery.value("y").toInt();
        locus.page = cartsQuery.value("page").toInt();
        newCart.title = cartsQuery.value("title").toString();
        newCart.theme.bgColour =
            getColourFromHexString(cartsQuery.value("bg_colour").toString());
        newCart.theme.textColour =
            getColourFromHexString(cartsQuery.value("text_colour").toString());

        newCart.locus = locus;

        destMap.insert({locus, newCart});
    }

    callback();
}

void CartModel::processCartWall(QSqlQuery &data, cartMap &destMap,
                                std::function<void ()> callback)
{
    std::list<unsigned int> cartWalls;

    if (!data.exec()) {
        requestError(data.lastError().text());
        return;
    }

    while (data.next())
        cartWalls.push_back(data.value("id").toInt());

    // If there are no cart walls, there's nothing we can do.  Call
    // the ready callback and just return.
    if (!cartWalls.size()) {
        callback();
        return;
    }

    processCarts(cartWalls.front(), destMap, callback);
}
