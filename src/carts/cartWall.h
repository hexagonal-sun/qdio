#ifndef CARTWALL_H
#define CARTWALL_H

#include <QWidget>
#include <QGridLayout>
#include <QStackedWidget>

#include "cartPageButton.h"

class CartWall : public QWidget
{
    Q_OBJECT
public:
    explicit CartWall(QWidget *parent = nullptr,
                      int cartWallId = 0);

private:
    int cartWallId_;
    QGridLayout *gridLayout_;
    QStackedWidget * createCartButtonStack(void);
    std::vector<std::vector<QStackedWidget *>> buttonStacks;
    std::vector<CartPageButton *>pageButtons;
};

#endif // CARTWALL_H
