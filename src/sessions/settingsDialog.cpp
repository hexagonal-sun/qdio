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
    settings_.setValue("apiUrl", ui->editRestURL->text());

    accept();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
