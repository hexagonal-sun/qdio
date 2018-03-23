#include "settingsDialog.h"
#include "ui_settingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->editRestURL->setText(settings_.value("apiUrl").toString());

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &SettingsDialog::accepted);
}

void SettingsDialog::accepted()
{
    QString url = ui->editRestURL->text();

    if (!url.endsWith('/'))
        url.append("/");

    settings_.setValue("apiUrl", url);

    accept();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
