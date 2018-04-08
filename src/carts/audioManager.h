#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <functional>
#include <queue>
#include <set>
#include <QObject>
#include <QMediaPlayer>

typedef std::pair<QString, std::function<void(qint64)>> durationRequest;

class AudioManager : public QObject
{
    Q_OBJECT
public:
    AudioManager(QObject *parent = nullptr,
                 unsigned int noMediaPlayers = 5);

    QMediaPlayer* acquireMediaPlayer(void);
    void releaseMediaPlayer(QMediaPlayer *player);
    void obtainDuration(QString file, std::function<void(qint64)> callback);
    void stopAll(void);

private:
    std::set<QMediaPlayer *> allMediaPlayers_;
    std::queue<QMediaPlayer *> ownedMediaPlayers_;
    void serviceDurationRequest(QMediaPlayer *mp, durationRequest req);
    std::queue<durationRequest> pendingDurationRequests;
};

#endif // AUDIOMANAGER_H
