#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QString>
#include <QWidget>

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
    const unsigned int getUserId(void) const;
    const QString& getAuthToken(void) const;
    const QString& getApiURL(void) const;
    const unsigned int getShowId(void) const;

private:
    SessionManager();
    QWidget *curWidget_;
    QString authToken_;
    QString apiUrl_;
    unsigned int userId_;
    unsigned int showId_;
    unsigned int stationId_;
};

#endif // SESSIONMANAGER_H
