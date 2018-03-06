#include <QCoreApplication>
#include <QVariant>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>

#include "cartsWindow.h"

CartsWindow::CartsWindow(QWidget *parent) :
    QMainWindow(parent),
    cartsRequest("carts/1/")
{
    centralWidget = new QWidget(this);

    setCentralWidget(centralWidget);
    gridLayout = new QGridLayout(centralWidget);

    for (uint32_t x = 0; x < 4; x++) {
        std::vector<CartButton *>buttonRow;
        for (uint32_t y = 0; y < 4; y++) {
            QString title = "";

            auto btn = new CartButton(centralWidget, title,
                                      QString::number(x + y, 10));

            btn->setEnabled(false);

            buttonRow.push_back(btn);

            gridLayout->addWidget(btn, x, y);
        }
        buttons.push_back(buttonRow);
    }


    connect(&cartsRequest, &RestRequest::requestFinished,
            [=](const QJsonDocument &json) {
        for (const auto cart : json.array()) {
            QJsonObject cartObj = cart.toObject();
            QString title = cartObj["title"].toString();
            int x = cartObj["xpos"].toInt();
            int y = cartObj["ypos"].toInt();

            buttons[x][y]->setCartTitle(title);
            buttons[x][y]->setEnabled(true);
        }
    });

    connect(&cartsRequest, &RestRequest::requestError,
            [=](const QString errorString) {
                QMessageBox::warning(this, "Network failure",
                                     "Could not obtain cart list: " +
                                     errorString);
            });

    cartsRequest.execute();
}

CartsWindow::~CartsWindow()
{
    for (auto btnRow : buttons)
        for (auto btn : btnRow)
            delete btn;

    delete gridLayout;
    delete centralWidget;
}
