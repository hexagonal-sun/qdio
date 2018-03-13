#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <map>

#include "restRequest.h"

namespace Ui {
class ShowDialog;
}

class ShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowDialog(QWidget *parent = 0);
    ~ShowDialog();

private slots:
    void showRequestFinished(const QJsonDocument &reply);
    void showRequestError(const QString &errorString, QNetworkReply::NetworkError error);
    void showSelectionComplete();
    void showSelectionCancelled();


private:
    Ui::ShowDialog *ui;
    RestRequest showRequest;
    std::map<QListWidgetItem *, int> showIdMap;
};

#endif // SHOWDIALOG_H
