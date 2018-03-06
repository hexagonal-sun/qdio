#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QNetworkAccessManager>
#include <vector>

#include "cartButton.h"
#include "restRequest.h"

class CartsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CartsWindow(QWidget *parent = 0);
    ~CartsWindow();

private:
    std::vector<std::vector<CartButton *>> buttons;
    RestRequest cartsRequest;
    QGridLayout *gridLayout;
    QWidget *centralWidget;
    static auto constexpr noCarts = 4 * 4; // 4 x 4 grid of carts.
};
