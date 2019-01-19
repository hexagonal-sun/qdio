#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>

#include "sessionManager.h"

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
    void showSettingsDialog(void);
private:
    void showErrorMessage(QString errorText);
    void setControlsEnabled(bool state);
    Ui::AuthDialog *ui;
};

#endif // AUTHDIALOG_H
