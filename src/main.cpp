#include "authDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("qdio");
    a.setOrganizationName("Qdio Ltd");
    a.setOrganizationDomain("qdio.co");

    SessionManager::getInstance().begin();

    return a.exec();
}
