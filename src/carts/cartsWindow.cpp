#include <QVBoxLayout>

#include "cartsWindow.h"
#include "controlButton.h"
#include "cartWall.h"
#include "audioManager.h"

CartsWindow::CartsWindow(QWidget *parent) :
    QMainWindow(parent)
{
    AudioManager *audioMan = new AudioManager(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *controlButtonLayout = new QHBoxLayout(this);
    CartWall *topCartWall = new CartWall(this, 0);
    CartWall *bottomCartWall = new CartWall(this, 1);
    QWidget *mainWidget = new QWidget(this);
    ControlButton *logoutButton = new ControlButton(this);
    ControlButton *stopAllButton = new ControlButton(this);

    logoutButton->setText("Logout");
    stopAllButton->setText("Stop All");

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
