#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

#include "restRequest.h"

RestRequest::RestRequest(const QString requestUrl)
    : requestUrl_(requestUrl),
      netManager_(this)
{
    connect(&netManager_, &QNetworkAccessManager::finished,
            this, &RestRequest::networkRequestFinished);
}

void RestRequest::execute(void)
{
    QUrl url("http://localhost:8000/" + requestUrl_);

    netManager_.get(QNetworkRequest(url));
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
            emit requestError(parseError.errorString());
        else
            emit requestFinished(json);
    } else
        emit requestError(reply->errorString());

    reply->deleteLater();
}
