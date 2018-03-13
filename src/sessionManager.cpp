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
    curWidget_ = new AuthDialog();

    authToken_ = "";
    showId_ = 0;
    stationId_ = 0;

    curWidget_->show();
}

void SessionManager::authFinished(QString &authToken)
{
    authToken_ = authToken;

    curWidget_->close();
    curWidget_->deleteLater();

    curWidget_ = new ShowDialog;
    curWidget_->show();
}

void SessionManager::showSelectionComplete(int showId)
{
    showId_ = showId;

    curWidget_->close();
    curWidget_->deleteLater();

    curWidget_ = new CartsWindow;
    curWidget_->show();
}

void SessionManager::showSelectionCancelled()
{
    curWidget_->close();
    curWidget_->deleteLater();
    curWidget_ = NULL;

    begin();
}

const QString& SessionManager::getAuthToken(void) const
{
    return authToken_;
}
