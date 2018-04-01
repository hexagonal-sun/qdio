#include "audioManager.h"

AudioManager::AudioManager(QObject *parent,
                           unsigned int noMediaPlayers) : QObject(parent)
{
    for (size_t i = 0; i < noMediaPlayers; i++) {
        QMediaPlayer *mp = new QMediaPlayer(this);

        mp->setNotifyInterval(100);
        mediaPlayers_.push(mp);
    }
}

QMediaPlayer* AudioManager::acquireMediaPlayer(void)
{
    if (mediaPlayers_.empty())
        return nullptr;

    QMediaPlayer *ret = mediaPlayers_.front();
    mediaPlayers_.pop();

    return ret;
}

void AudioManager::releaseMediaPlayer(QMediaPlayer *player)
{
    // Sanitize the obejct before pushing it back into the queue.
    disconnect(player, 0, 0, 0);

    if (!pendingDurationRequests.empty()) {
        auto request = pendingDurationRequests.front();
        pendingDurationRequests.pop();

        serviceDurationRequest(player, request);
        return;
    }

    mediaPlayers_.push(player);
}

void AudioManager::serviceDurationRequest(QMediaPlayer *mp, durationRequest req)
{
    connect(mp, &QMediaPlayer::mediaStatusChanged,
            [=](QMediaPlayer::MediaStatus status)
    {
        if (status != QMediaPlayer::LoadedMedia)
            return;

        req.second(mp->duration());
        releaseMediaPlayer(mp);
    });

    mp->setMedia(QUrl::fromLocalFile(req.first));
}

void AudioManager::obtainDuration(QString file,
                                    std::function<void(qint64)> callback)
{
    QMediaPlayer *mp = acquireMediaPlayer();
    auto durationRequest = std::make_pair(file, callback);

    if (!mp) {
        pendingDurationRequests.push(durationRequest);
        return;
    }

    serviceDurationRequest(mp, durationRequest);
}
