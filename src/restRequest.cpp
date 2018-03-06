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
