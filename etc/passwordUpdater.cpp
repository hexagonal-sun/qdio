#include <QString>
#include <random>
#include <QByteArray>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QTimer>
#include <QCoreApplication>
#include <QCryptographicHash>

class PasswordUpdater : public QObject
{
    Q_OBJECT

public:
    PasswordUpdater(QObject *parent = 0) : QObject(parent)
        {
        }

public slots:
    void run()
        {
            std::random_device rd;
            QByteArray saltBytes;

            std::string username;
            std::string password;
            QCryptographicHash hash(QCryptographicHash::Keccak_256);

            for (int i = 0; i < 4; i++)
                saltBytes.append(rd() & 0xff);

            hash.addData(saltBytes);

            std::cout << "Username: ";
            std::cin >> username;

            std::cout << "Password: ";
            std::cin >> password;

            hash.addData(password.c_str(), password.size());

            QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
            db.setDatabaseName("qdio");

            if (!db.open())
            {
                std::cerr << "Could not open database\n";
                QCoreApplication::instance()->exit(1);
                return;
            }

            QSqlQuery query;

            query.prepare("SELECT update_password(:name, :hash, :salt)");

            query.bindValue(":name", QString::fromStdString(username));
            query.bindValue(":hash", QString::fromStdString(hash.result().toHex(0).toStdString()));
            query.bindValue(":salt", QString::fromStdString(saltBytes.toHex(0).toStdString()));

            if (!query.exec())
            {
                std::cerr << "Could not execute query: ";
                std::cerr << query.lastError().text().toStdString() << std::endl;
                QCoreApplication::instance()->exit(1);
                return;
            }

            std::cout << "Password successfully updated.\n";

            QCoreApplication::instance()->exit(0);
        }
};

#include "passwordUpdater.moc"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    PasswordUpdater *pu = new PasswordUpdater(&app);

    QTimer::singleShot(0, pu, &PasswordUpdater::run);

    return app.exec();
}
