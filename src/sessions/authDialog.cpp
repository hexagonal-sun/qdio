#include <QMessageBox>
#include <QJsonObject>
#include <QPushButton>

#include "authDialog.h"
#include "sessionManager.h"
#include "settingsDialog.h"
#include "ui_authDialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    authRequest("api/auth/login/", false),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AuthDialog::accepted);
    connect(&authRequest, &RestRequest::requestFinished, this, &AuthDialog::authRequestFinished);
    connect(&authRequest, &RestRequest::requestError, this, &AuthDialog::authError);
    connect(ui->btnSettings, &QPushButton::pressed, this, &AuthDialog::showSettingsDialog);
}

void AuthDialog::accepted(void)
{
    QJsonObject record;

    setControlsEnabled(false);

    record.insert("username", QJsonValue::fromVariant(ui->editUsername->text()));
    record.insert("password", QJsonValue::fromVariant(ui->editPassword->text()));

    QJsonDocument document(record);

    authRequest.post(document);
}

void AuthDialog::showSettingsDialog(void)
{
    SettingsDialog settingsDlg;

    settingsDlg.exec();
}

void AuthDialog::authRequestFinished(const QJsonDocument &reply)
{
    QJsonObject obj = reply.object();
    QString authToken = obj["token"].toString();

    SessionManager::getInstance().authFinished(authToken);
}

void AuthDialog::authError(const QString &errorString, QNetworkReply::NetworkError error)
{
    QString userErrorString = errorString;

    if (error == QNetworkReply::ProtocolInvalidOperationError)
        userErrorString = "Invalid username or password.";

    QMessageBox::warning(this, "Authentication Failed",
                         "Authentication failed: " + userErrorString);

    setControlsEnabled(true);
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
