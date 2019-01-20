#include <QFileDialog>
#include "settingsDialog.h"
#include "ui_settingsDialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->editRestURL->setText(settings_.value("apiUrl").toString());
    ui->editAudioFileRoot->setText(settings_.value("audioFileRoot").toString());

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &SettingsDialog::accepted);

    connect(ui->buttonAudioFileRootBrowse, &QPushButton::clicked,
            this, &SettingsDialog::audioFileBrowseClick);
}

void SettingsDialog::accepted()
{
    QString url = ui->editRestURL->text();
    QString audioFileRoot = ui->editAudioFileRoot->text();

    if (!url.endsWith('/'))
        url.append("/");

    settings_.setValue("apiUrl", url);
    settings_.setValue("audioFileRoot", audioFileRoot);

    accept();
}

void SettingsDialog::audioFileBrowseClick()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    ui->editAudioFileRoot->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);

    ui->editAudioFileRoot->setText(dir);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
