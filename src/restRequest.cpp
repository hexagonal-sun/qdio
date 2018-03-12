#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "restRequest.h"
#include "authManager.h"

RestRequest::RestRequest(const QString requestUrl,
                         bool requiresAuth)
    : requestUrl_(requestUrl),
      requiresAuth_(requiresAuth),
      netManager_(this)
{
    connect(&netManager_, &QNetworkAccessManager::finished,
            this, &RestRequest::networkRequestFinished);
}

void RestRequest::get(void)
{
    QUrl url("http://localhost:8000/" + requestUrl_);

    QNetworkRequest request(url);

    if (requiresAuth_)
        request.setRawHeader("Authorization", "Token " +
                             AuthManager::getAuthToken().toUtf8());

    netManager_.get(request);
}

void RestRequest::post(QJsonDocument json)
{
    QUrl url("http://localhost:8000/" + requestUrl_);
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
