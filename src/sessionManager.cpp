#include "authDialog.h"
#include "sessionManager.h"
#include "cartsWindow.h"

SessionManager& SessionManager::getInstance(void)
{
    static SessionManager s;
    return s;
}

void SessionManager::begin(void)
{
    curWindget_ = new AuthDialog();

    authToken_ = "";
    showId_ = 0;
    stationId_ = 0;

    curWindget_->show();
}

void SessionManager::authFinished(QString &authToken)
{
    authToken_ = authToken;

    curWindget_->close();
    curWindget_->deleteLater();

    curWindget_ = new CartsWindow;
    curWindget_->show();
}

const QString& SessionManager::getAuthToken(void) const
{
    return authToken_;
}
