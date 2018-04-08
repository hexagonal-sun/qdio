#ifndef CARTWALL_H
#define CARTWALL_H

#include <QWidget>
#include <QGridLayout>
#include <QStackedWidget>

#include "cartPageButton.h"
#include "audioManager.h"
#include "cartModel.h"

class CartWall : public QWidget
{
    Q_OBJECT
public:
    CartWall(AudioManager *audioMan, CartModel *model,
             enum CartWallType type, QWidget *parent = nullptr);

private slots:
    void createCarts(AudioManager *audioMan);

private:
    QGridLayout *gridLayout_;
    QStackedWidget * createCartButtonStack(AudioManager *audioMan, unsigned int x,
                                           unsigned int y);
    std::vector<std::vector<QStackedWidget *>> buttonStacks;
    std::vector<CartPageButton *>pageButtons;
    enum CartWallType cartWallType_;
    CartModel *model_;
};

#endif // CARTWALL_H
