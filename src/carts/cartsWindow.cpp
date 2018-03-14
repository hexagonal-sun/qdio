#include <QVBoxLayout>

#include "cartsWindow.h"
#include "cartWall.h"

CartsWindow::CartsWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    CartWall *topCartWall = new CartWall(this, 0);
    CartWall *bottomCartWall = new CartWall(this, 1);
    QWidget *mainWidget = new QWidget(this);

    layout->addWidget(topCartWall);
    layout->addWidget(bottomCartWall);

    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
}
