#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>
#include <QSqlQuery>
#include <QSqlError>

#include "showDialog.h"
#include "sessionManager.h"
#include "ui_showDialog.h"

ShowDialog::ShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &ShowDialog::showSelectionComplete);

    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &ShowDialog::showSelectionCancelled);

    QSqlQuery showQuery;
    showQuery.prepare("SELECT * from get_shows_for_user(:uid)");
    showQuery.bindValue(":uid", SessionManager::getInstance().getUserId());

    if (!showQuery.exec())
    {
        QMessageBox mbox;

        mbox.critical(this, "Error retrieving shows",
                      "Could not obtain shows for this user\n\nDetails: " +
                      showQuery.lastError().text());

        return;
    }

    while (showQuery.next())
    {
        auto showId = showQuery.value("showid").toInt();
        auto showName = showQuery.value("showname").toString();

        QListWidgetItem *newItem = new QListWidgetItem(showName);
        showIdMap[newItem] = showId;

        ui->showList->addItem(newItem);
    }
}

void ShowDialog::showSelectionComplete()
{
    QListWidgetItem *selectedItem = ui->showList->currentItem();
    int showId;

    if (!selectedItem) {
        QMessageBox::information(this, "Show Selection",
                                 "Please slect a show from the list");

        return;
    }

    showId = showIdMap[selectedItem];

    SessionManager::getInstance().showSelectionComplete(showId);
}

void ShowDialog::showSelectionCancelled()
{
    SessionManager::getInstance().showSelectionCancelled();
}

ShowDialog::~ShowDialog()
{
    for (auto showIdMapping : showIdMap)
        delete showIdMapping.first;

    delete ui;
}
