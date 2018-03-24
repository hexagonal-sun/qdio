#include <QAudioDeviceInfo>

#include "cartAudioManager.h"

CartAudioManager::CartAudioManager(QObject *parent,
                                   const QString &audioFile)
    : QObject(parent),
      audioBuffer_(nullptr),
      decodingComplete_(false)
{
    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    outputFormat_ = info.preferredFormat();

    decoder_ = new QAudioDecoder(this);
    output_ = new QAudioOutput(outputFormat_, this);

    output_->setNotifyInterval(100);

    decoder_->setAudioFormat(outputFormat_);
    decoder_->setSourceFilename(audioFile);

    connect(decoder_, &QAudioDecoder::bufferReady,
            this, &CartAudioManager::bufferFrames);

    connect(decoder_, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error),
            [=](QAudioDecoder::Error err){ emit decodingError(); });

    connect(decoder_, &QAudioDecoder::durationChanged,
            [=]{ emit durationUpdate(); });

    connect(output_, &QAudioOutput::notify,
            [=]{ emit positionUpdate(); });

    connect(decoder_, &QAudioDecoder::stateChanged,
            [=](QAudioDecoder::State state)
            {
                if (state == QAudioDecoder::StoppedState) {
                    emit decodingComplete();
                    decodingComplete_ = true;
                }
            });

    connect(output_, &QAudioOutput::stateChanged,
            [=](QAudio::State state)
            {
                if (state == QAudio::IdleState) {
                    emit playbackFinished();
                    stop();
                }
            });

    decoder_->start();
}

qint64 CartAudioManager::getAudioDuration(void) const
{
    return decoder_->duration();
}

qint64 CartAudioManager::getAudioPosition(void) const
{
    return output_->elapsedUSecs() / 1000;
}

bool CartAudioManager::isPlaying(void) const
{
    return audioBuffer_ != nullptr;
}

void CartAudioManager::bufferFrames(void)
{
    while (decoder_->bufferAvailable()) {
        QAudioBuffer buf = decoder_->read();

        decodedAudio_.append(buf.constData<char>(), buf.byteCount());
    }
}

void CartAudioManager::play(void)
{
    if (!decodingComplete_)
        return;

    if (audioBuffer_ != nullptr)
        stop();

    audioBuffer_ = new QBuffer(&decodedAudio_, this);
    audioBuffer_->open(QBuffer::ReadOnly);
    output_->start(audioBuffer_);
}

void CartAudioManager::stop(void)
{
    if (!audioBuffer_)
        return;

    output_->stop();
    delete audioBuffer_;
    audioBuffer_ = nullptr;
}
