#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>

#include "restRequest.h"

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();

private slots:
    void accepted(void);
    void authRequestFinished(const QJsonDocument &reply);
    void authError(const QString &errorString);

private:
    void setControlsEnabled(bool state);
    Ui::AuthDialog *ui;
    RestRequest authRequest;
};

#endif // AUTHDIALOG_H
