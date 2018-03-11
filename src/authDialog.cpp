#include <QMessageBox>
#include <QJsonObject>

#include "authDialog.h"
#include "ui_authDialog.h"

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    authRequest("api/auth/login/"),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AuthDialog::accepted);
    connect(&authRequest, &RestRequest::requestFinished, this, &AuthDialog::authRequestFinished);
    connect(&authRequest, &RestRequest::requestError, this, &AuthDialog::authError);
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

void AuthDialog::authRequestFinished(const QJsonDocument &reply)
{
    QJsonObject obj = reply.object();
    QString authToken = obj["token"].toString();

    QMessageBox::information(this, "foo", authToken);

    accept();
}

void AuthDialog::authError(const QString &errorString)
{
    QMessageBox::warning(this, "Authentication Failed",
                         "Authentication failed: " + errorString);

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
