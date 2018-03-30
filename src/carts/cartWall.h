#ifndef CARTWALL_H
#define CARTWALL_H

#include <QWidget>
#include <QGridLayout>
#include <QStackedWidget>

#include "cartPageButton.h"
#include "audioManager.h"

class CartWall : public QWidget
{
    Q_OBJECT
public:
    explicit CartWall(AudioManager *audioMan, QWidget *parent = nullptr,
                      int cartWallId = 0);

private:
    int cartWallId_;
    QGridLayout *gridLayout_;
    QStackedWidget * createCartButtonStack(AudioManager *audioMan);
    std::vector<std::vector<QStackedWidget *>> buttonStacks;
    std::vector<CartPageButton *>pageButtons;
};

#endif // CARTWALL_H
