#include "authDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SessionManager::getInstance().begin();

    return a.exec();
}
