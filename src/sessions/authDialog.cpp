#include <QCryptographicHash>
#include <QByteArray>
#include <QMessageBox>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlError>

#include "authDialog.h"
#include "sessionManager.h"
#include "settingsDialog.h"
#include "ui_authDialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AuthDialog::accepted);
    connect(ui->btnSettings, &QPushButton::pressed, this, &AuthDialog::showSettingsDialog);
}

void AuthDialog::accepted(void)
{
    auto username = ui->editUsername->text();
    auto password = ui->editPassword->text();

    QSqlQuery userQuery;
    userQuery.prepare("SELECT * "
                      "FROM  find_user(:username) "
                      "AS f(user_id integer, salt varchar)");

    userQuery.bindValue(":username", username);

    if (!userQuery.exec())
    {
        showErrorMessage("Invalid username or password");
        return;
    }

    userQuery.first();

    int userId = userQuery.value("user_id").toInt();
    auto salt = QByteArray::fromHex(userQuery.value("salt").toByteArray());

    QCryptographicHash hash(QCryptographicHash::Keccak_256);

    hash.addData(salt);
    hash.addData(password.toStdString().c_str(), password.size());

    QSqlQuery loginQuery;
    loginQuery.prepare("SELECT user_login(:uid, :hash)");
    loginQuery.bindValue(":uid", userId);
    loginQuery.bindValue(":hash",
                         QString::fromStdString(hash.result().toHex(0).toStdString()));


    if (!loginQuery.exec())
    {
        showErrorMessage("Could not perform login query\n\nDetails:" +
                         loginQuery.lastError().text());

        return;
    }

    loginQuery.first();

    bool loginSuccessful = loginQuery.value(0).toBool();

    if (!loginSuccessful)
    {
        showErrorMessage("Invalid username or password");
        return;
    }

    SessionManager::getInstance().authFinished(userId);
}

void AuthDialog::showErrorMessage(QString errorText)
{
    QMessageBox mbox;

    mbox.critical(this, "Authentication Error",
                  "Error: " + errorText);

    mbox.exec();
}

void AuthDialog::showSettingsDialog(void)
{
    SettingsDialog settingsDlg;

    settingsDlg.exec();

    SessionManager::getInstance().reloadSettings();
}

void AuthDialog::setControlsEnabled(bool state)
{
    ui->editPassword->setEnabled(state);
    ui->editUsername->setEnabled(state);
    ui->buttonBox->setEnabled(state);
}

AuthDialog::~AuthDialog()
{
    delete ui;
}
