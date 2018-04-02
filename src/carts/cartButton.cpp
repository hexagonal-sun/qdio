#include <QDebug>
#include <QPainter>

#include "cartButton.h"

CartButton::CartButton(QWidget *parent, QString text, QString file,
                       AudioManager *audioMan)
    : QAbstractButton(parent),
      cartState_(LOADING),
      position_(0),
      duration_(0),
      mediaPlayer_(nullptr),
      audioMan_(audioMan),
      redFlash_(false)
{
    setupAppearance();
    setText(text);

    connect(this, &QAbstractButton::released,
            this, &CartButton::clicked);

    connect(&flashTimer_, &QTimer::timeout,
            this, &CartButton::flashTimeout);

    audioMan->obtainDuration("/home/matthew/test.mp3",
                             [=](qint64 newDuration)
        {
            duration_ = newDuration;
            setEnabled(true);
            cartState_ = READY;
            update();
        });
}

CartButton::CartButton(QWidget *parent)
    : QAbstractButton(parent),
      cartState_(EMPTY),
      redFlash_(false)
{
    setupAppearance();
}

void CartButton::clicked()
{
    if (mediaPlayer_ != nullptr) {
        mediaPlayer_->stop();
        return;
    }

    mediaPlayer_ = audioMan_->acquireMediaPlayer();

    if (!mediaPlayer_)
        return;

    mediaPlayer_->setMedia(QUrl::fromLocalFile("/home/matthew/test.mp3"));

    // When we recieve a position update, update() the widget so that
    // the new duration is painted.
    connect(mediaPlayer_, &QMediaPlayer::positionChanged,
            [=](qint64 newPosition){ position_ = newPosition; update(); });

    connect(mediaPlayer_, &QMediaPlayer::stateChanged,
            [=](QMediaPlayer::State newState)
    {
        if (newState == QMediaPlayer::StoppedState)
            stopAndReset();
    });

    mediaPlayer_->play();
    flashTimer_.start(500);
    emit cartPlaybackStrarted();
}

void CartButton::stopAndReset(void)
{
    mediaPlayer_->stop();
    audioMan_->releaseMediaPlayer(mediaPlayer_);
    mediaPlayer_ = nullptr;

    flashTimer_.stop();
    redFlash_ = false;

    position_ = 0;
    update();

    emit cartPlaybackStopped();
}

void CartButton::setupAppearance(void)
{
    QFont widgetFont = font();

    widgetFont.setBold(true);
    widgetFont.setPointSize(widgetFont.pointSize() * 1.5);

    setFont(widgetFont);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

const int CartButton::calculateMinimumWidth() const
{
    QFontMetrics widgetFontMetrics(font());

    return widgetFontMetrics.width(getCartText());
}

QSize CartButton::sizeHint() const
{
    QFontMetrics widgetFontInfo(font());

    return QSize(calculateMinimumWidth() * 1.3,
                 widgetFontInfo.height() * 4);
}

QSize CartButton::minimumSizeHint() const
{
    QFontMetrics widgetFontInfo(font());

    return QSize(calculateMinimumWidth(),
                 widgetFontInfo.height() * 3);
}

void CartButton::flashTimeout()
{
    redFlash_ = !redFlash_;
}

const QString CartButton::getCartText() const
{
    QString ret;

    switch (cartState_)
    {
    case LOADING:
        return "Loading";
    case EMPTY:
        return "Empty";
    case ERROR:
        return "Load Error";
    case READY:
    {
        QString ret;
        qint64 timeLeft = duration_ - position_;

        ret.sprintf("%s\n\n%0.1f", text().toStdString().c_str(),
                    (double)timeLeft / 1000);

        return ret;
    }
    }
}

bool CartButton::isReady(void) const
{
    return cartState_ == READY;
}

void CartButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    auto bgColour = isReady() ? Qt::darkBlue : Qt::black;
    auto txtColour = isReady() ? Qt::white : Qt::gray;

    if (redFlash_)
        bgColour = Qt::red;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(bgColour);
    painter.drawRect(pe->rect());

    painter.setPen(QPen(txtColour));

    painter.drawText(pe->rect(), Qt::AlignCenter, getCartText());
}
