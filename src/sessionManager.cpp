#include "authDialog.h"
#include "sessionManager.h"
#include "cartsWindow.h"
#include "showDialog.h"

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

    curWindget_ = new ShowDialog;
    curWindget_->show();
}

void SessionManager::showSelectionComplete(int showId)
{
    showId_ = showId;

    curWindget_->close();
    curWindget_->deleteLater();

    curWindget_ = new CartsWindow;
    curWindget_->show();
}

void SessionManager::showSelectionCancelled()
{
    curWindget_->close();
    curWindget_->deleteLater();
    curWindget_ = NULL;

    begin();
}

const QString& SessionManager::getAuthToken(void) const
{
    return authToken_;
}
