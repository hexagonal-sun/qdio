#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "restRequest.h"
#include "sessionManager.h"

RestRequest::RestRequest(const QString requestUrl,
                         bool requiresAuth,
                         QObject *parent)
    : requestUrl_(requestUrl),
      requiresAuth_(requiresAuth),
      QObject(parent),
      netManager_(this)
{
    connect(&netManager_, &QNetworkAccessManager::finished,
            this, &RestRequest::networkRequestFinished);
}

void RestRequest::get(void)
{
    QUrl url(SessionManager::getInstance().getApiURL() + requestUrl_);

    QNetworkRequest request(url);

    if (requiresAuth_)
        request.setRawHeader("Authorization", "Token " +
                             SessionManager::getInstance().getAuthToken().toUtf8());

    netManager_.get(request);
}

void RestRequest::doGetRequest(const QString url, bool requiresAuth,
                               QObject *parent, successCallback_t successCallback,
                               errorCallback_t errorCallback)
{
    RestRequest *newRequest = new RestRequest(url, requiresAuth, parent);

    connect(newRequest, &RestRequest::requestFinished, successCallback);
    connect(newRequest, &RestRequest::requestError, errorCallback);

    newRequest->get();
}

void RestRequest::post(QJsonDocument json)
{
    QUrl url(SessionManager::getInstance().getApiURL() + requestUrl_);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    netManager_.post(request, json.toJson());
}

void RestRequest::networkRequestFinished(QNetworkReply *reply)
{
    QJsonParseError parseError;
    QJsonDocument json;

    if (reply->error() == QNetworkReply::NoError) {
        json = QJsonDocument::fromJson(reply->readAll(), &parseError);

        if (json.isNull())
            emit requestError(parseError.errorString(), reply->error());
        else
            emit requestFinished(json);
    } else
        emit requestError(reply->errorString(),  reply->error());

    reply->deleteLater();
}
