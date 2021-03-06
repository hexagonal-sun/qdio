#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>
#include <QWidget>
#include <QDir>

class SessionManager : public QObject
{
    Q_OBJECT
public:
    SessionManager(SessionManager const &s) = delete;
    void operator=(SessionManager const &s) = delete;

    static SessionManager& getInstance(void);

    void begin(void);
    void authFinished(int userId);
    void showSelectionComplete(int showId);
    void showSelectionCancelled();
    void reloadSettings(void);
    void logout(void);
    unsigned int getUserId(void) const;
    const QString& getAuthToken(void) const;
    const QString& getApiURL(void) const;
    unsigned int getShowId(void) const;
    QDir getAudioRootDir(void) const;

private:
    SessionManager();
    QWidget *curWidget_;
    QString authToken_;
    QString apiUrl_;
    QDir audioRoot_;
    unsigned int userId_;
    unsigned int showId_;
    unsigned int stationId_;
};

#endif // SESSIONMANAGER_H
