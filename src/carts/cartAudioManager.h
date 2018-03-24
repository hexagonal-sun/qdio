#pragma once

#include <QAudioDecoder>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QIODevice>
#include <QBuffer>

class CartAudioManager : public QObject
{
    Q_OBJECT

public:
    CartAudioManager(QObject *parent, const QString &audioFile);
    qint64 getAudioDuration(void) const;
    qint64 getAudioPosition(void) const;
    bool isPlaying(void) const;
    void play(void);
    void stop(void);

signals:
    void decodingComplete(void);
    void decodingError(void);
    void durationUpdate(void);
    void positionUpdate(void);
    void playbackFinished(void);

private slots:
    void bufferFrames(void);

private:
    QAudioDecoder *decoder_;
    QAudioOutput *output_;
    QAudioFormat outputFormat_;
    bool decodingComplete_;
    QByteArray decodedAudio_;
    QBuffer *audioBuffer_;
};
