#include <QVBoxLayout>

#include "cartsWindow.h"
#include "controlButton.h"
#include "cartWall.h"
#include "audioManager.h"
#include "cartModel.h"
#include "sessionManager.h"

CartsWindow::CartsWindow(QWidget *parent) :
    QMainWindow(parent)
{
    CartModel *cartModel = new CartModel(this);
    AudioManager *audioMan = new AudioManager(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *controlButtonLayout = new QHBoxLayout(this);
    CartWall *topCartWall = new CartWall(audioMan, cartModel, CartWallType::STATION, this);
    CartWall *bottomCartWall = new CartWall(audioMan, cartModel, CartWallType::SHOW, this);
    QWidget *mainWidget = new QWidget(this);
    ControlButton *logoutButton = new ControlButton(this);
    ControlButton *stopAllButton = new ControlButton(this);

    logoutButton->setText("Logout");
    stopAllButton->setText("Stop All");

    connect(logoutButton, &QPushButton::released,
            [=]{ SessionManager::getInstance().logout(); });

    connect(stopAllButton, &QPushButton::released,
            [=]{ audioMan->stopAll(); });

    controlButtonLayout->addStretch();
    controlButtonLayout->addWidget(logoutButton);
    controlButtonLayout->addSpacing(35);
    controlButtonLayout->addWidget(stopAllButton);
    controlButtonLayout->addStretch();

    layout->addWidget(topCartWall);
    layout->addLayout(controlButtonLayout);
    layout->addWidget(bottomCartWall);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}
