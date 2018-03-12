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
    void authFinished(QString &authToken);
    const QString& getAuthToken(void) const;

private:
    SessionManager() = default;
    QWidget *curWindget_;
    QString authToken_;
    unsigned int showId_;
    unsigned int stationId_;
};

#endif // SESSIONMANAGER_H
