#ifndef CARTWALL_H
#define CARTWALL_H

#include <QWidget>
#include <QGridLayout>

#include "cartButton.h"

class CartWall : public QWidget
{
    Q_OBJECT
public:
    explicit CartWall(QWidget *parent = nullptr,
                      int cartWallId = 0);
private:
    int cartWallId_;
    QGridLayout *gridLayout_;
    std::vector<std::vector<CartButton *>> buttons;
    static auto constexpr noCarts = 4 * 4; // 4 x 4 grid of carts.
};

#endif // CARTWALL_H
