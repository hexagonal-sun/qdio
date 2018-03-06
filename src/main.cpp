#include "cartsWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CartsWindow w;
    w.show();

    return a.exec();
}
