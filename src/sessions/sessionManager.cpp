#include <QSettings>
#include <QSqlDatabase>

#include "authDialog.h"
#include "sessionManager.h"
#include "cartsWindow.h"
#include "showDialog.h"

SessionManager::SessionManager()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("qdio");
    db.open();
}

SessionManager& SessionManager::getInstance(void)
{
    static SessionManager s;
    return s;
}

void SessionManager::begin(void)
{
    QSettings settings;
    curWidget_ = new AuthDialog();

    userId_ = 0;
    showId_ = 0;
    stationId_ = 0;
    audioRoot_ = QDir(settings.value("audioFileRoot").toString());

    reloadSettings();

    curWidget_->show();
}

void SessionManager::reloadSettings(void)
{
    QSettings set;

    apiUrl_ = set.value("apiUrl").toString();
}

void SessionManager::authFinished(int userId)
{
    userId_ = userId;

    curWidget_->close();
    curWidget_->deleteLater();

    curWidget_ = new ShowDialog;
    curWidget_->show();
}

const QString& SessionManager::getAuthToken(void) const
{
    return "";
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

void SessionManager::logout()
{
    curWidget_->close();
    curWidget_->deleteLater();

    begin();
}

unsigned int SessionManager::getUserId(void) const
{
    return userId_;
}

const QString &SessionManager::getApiURL(void) const
{
    return apiUrl_;
}

unsigned int SessionManager::getShowId(void) const
{
    return showId_;
}

QDir SessionManager::getAudioRootDir(void) const
{
    return audioRoot_;
}
