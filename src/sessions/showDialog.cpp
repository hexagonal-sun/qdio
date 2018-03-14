#include <QMessageBox>
#include <QJsonArray>
#include <QJsonObject>

#include "showDialog.h"
#include "sessionManager.h"
#include "ui_showDialog.h"

ShowDialog::ShowDialog(QWidget *parent) :
    QDialog(parent),
    showRequest("api/qdio/shows/"),
    ui(new Ui::ShowDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted,
            this, &ShowDialog::showSelectionComplete);

    connect(ui->buttonBox, &QDialogButtonBox::rejected,
            this, &ShowDialog::showSelectionCancelled);

    connect(&showRequest, &RestRequest::requestFinished,
            this, &ShowDialog::showRequestFinished);

    connect(&showRequest, &RestRequest::requestError,
            this, &ShowDialog::showRequestError);

    showRequest.get();
}

void ShowDialog::showRequestFinished(const QJsonDocument &reply)
{
    for (const auto show : reply.array()) {
        QJsonObject showObj = show.toObject();
        QString showName = showObj["title"].toString();
        int showId = showObj["id"].toInt();
        QListWidgetItem *newItem = new QListWidgetItem(showName);
        showIdMap[newItem] = showId;

        ui->showList->addItem(newItem);
    }
}

void ShowDialog::showRequestError(const QString &errorString,
                                  QNetworkReply::NetworkError error)
{
    QMessageBox::warning(this, "Error",
                         "Error: could not obtain show list: " + errorString);

    SessionManager::getInstance().showSelectionCancelled();
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
