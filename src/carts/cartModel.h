#ifndef CARTMODEL_H
#define CARTMODEL_H

#include <QSqlQuery>
#include <QObject>
#include <QString>
#include <QColor>
#include <list>
#include <functional>
#include <unordered_map>

#include "audioManager.h"
#include "cartButton.h"

enum class CartWallType {
    STATION,
    SHOW,
    USER
};

struct cartTheme {
    QString name;
    QColor textColour;
    QColor bgColour;
};

struct cartLocus {
    unsigned int x;
    unsigned int y;
    unsigned int page;

    bool operator ==(const struct cartLocus &other) const
    {
        return x == other.x && y == other.y && page == other.page;
    }
};

struct cartProperties {
    struct cartTheme theme;
    struct cartLocus locus;
    QString title;
};

namespace std
{
    template <>
    struct hash<struct cartLocus>
    {
        size_t operator()(const struct cartLocus &locus) const
        {
            return hash<int>()(locus.x) ^
                   hash<int>()(locus.y) ^
                   hash<int>()(locus.page);
        }
    };
}

typedef std::unordered_map<struct cartLocus, struct cartProperties> cartMap;

class CartModel : public QObject
{
    Q_OBJECT
public:
    CartModel(QObject *parent);
    bool isReady(void) const;
    CartButton *getButton(const CartWallType &cartWall,
                          const struct cartLocus &locus,
                          AudioManager *audioMan,
                          QWidget *parent) const;

signals:
    void modelReady() const;
    void modelError(const QString error) const;

private slots:
    void processCarts(int cartWallId, cartMap &destMap,
                      std::function<void ()> callback);

    void processCartWall(QSqlQuery &data, cartMap &destMap,
                         std::function<void()> callback);


private:
    void requestError(const QString &errorString) const;
    void stationCartsReady(void);
    void showCartsReady(void);
    void checkReady(void) const;
    bool showCartsReady_;
    bool stationCartsReady_;
    QColor getColourFromHexString(const QString &value) const;
    std::list<unsigned int> stationCartWalls_;
    std::list<unsigned int> showCartWalls_;

    const std::unordered_map<enum CartWallType, cartMap &> cartWallTypeMap_;

    cartMap stationCarts_;
    cartMap showCarts_;
    cartMap userCarts_;
};

#endif
