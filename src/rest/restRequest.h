#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QObject>
#include <QString>

class RestRequest : public QObject
{
    Q_OBJECT
public:
    explicit RestRequest(const QString requestUrl,
                         bool requiresAuth = true,
                         QObject *parent = nullptr);
    void get(void);
    void post(QJsonDocument payload);

signals:
    void requestFinished(const QJsonDocument &restData);
    void requestError(const QString errorString, QNetworkReply::NetworkError error);

private:
    bool requiresAuth_;
    const QString requestUrl_;
    void networkRequestFinished(QNetworkReply *rep);
    QNetworkAccessManager netManager_;
};
