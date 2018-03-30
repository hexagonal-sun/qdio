#include "audioManager.h"

AudioManager::AudioManager(QObject *parent,
                           unsigned int noMediaPlayers) : QObject(parent)
{
    for (size_t i = 0; i < noMediaPlayers; i++)
        mediaPlayers_.push(new QMediaPlayer(this));
}

QMediaPlayer* AudioManager::acquireMediaPlayer(void)
{
    if (mediaPlayers_.empty())
        return NULL;

    QMediaPlayer *ret = mediaPlayers_.front();
    mediaPlayers_.pop();

    return ret;
}

void AudioManager::releaseMediaPlayer(QMediaPlayer *player)
{
    // Sanitize the obejct before pushing it back into the queue.
    player->disconnect();

    mediaPlayers_.push(player);
}
