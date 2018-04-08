#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QObject>
#include <QString>

typedef std::function<void (const QJsonDocument &)> successCallback_t;
typedef std::function<void (const QString &, QNetworkReply::NetworkError)> errorCallback_t;

class RestRequest : public QObject
{
    Q_OBJECT
public:
    explicit RestRequest(const QString requestUrl,
                         bool requiresAuth = true,
                         QObject *parent = nullptr);
    void get(void);
    void post(QJsonDocument payload);

    static void doGetRequest(const QString url,
                             bool requiresAuth, QObject *parent,
                             successCallback_t tfinishedCallback,
                             errorCallback_t errorCallback);

signals:
    void requestFinished(const QJsonDocument &restData);
    void requestError(const QString errorString, QNetworkReply::NetworkError error);

private:
    bool requiresAuth_;
    const QString requestUrl_;
    void networkRequestFinished(QNetworkReply *rep);
    QNetworkAccessManager netManager_;
};
