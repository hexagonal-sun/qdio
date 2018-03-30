#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <QObject>
#include <queue>
#include <QMediaPlayer>

class AudioManager : public QObject
{
    Q_OBJECT
public:
    AudioManager(QObject *parent = nullptr,
                 unsigned int noMediaPlayers = 5);

    QMediaPlayer* acquireMediaPlayer(void);
    void releaseMediaPlayer(QMediaPlayer *player);
signals:

public slots:

private:
    std::queue<QMediaPlayer *> mediaPlayers_;
};

#endif // AUDIOMANAGER_H
