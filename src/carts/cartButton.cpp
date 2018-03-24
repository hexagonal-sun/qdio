#include "cartButton.h"
#include <QDebug>
#include <QPainter>

CartButton::CartButton(QWidget *parent, QString text, QString file)
    : QAbstractButton(parent),
      cartState_(LOADING),
      redFlash_(false)
{
    setupAppearance();
    setText(text);

    audioManager_ = new CartAudioManager(this, "/home/matthew/test.mp3");

    connect(audioManager_, &CartAudioManager::decodingComplete,
            [=]{ cartState_ = READY; setEnabled(true); });

    connect(audioManager_, &CartAudioManager::decodingError,
            [=]{ cartState_ = ERROR; });

    // When we recieve a duration update, update() the widget so that
    // the new duration is painted.
    connect(audioManager_, &CartAudioManager::durationUpdate,
            [=]{ update(); });

    connect(audioManager_, &CartAudioManager::positionUpdate,
            [=]{ update(); });

    connect(audioManager_, &CartAudioManager::playbackFinished,
            [=]{ stopAndReset(); });

    connect(this, &QAbstractButton::released,
            this, &CartButton::clicked);

    connect(&flashTimer_, &QTimer::timeout,
            this, &CartButton::flashTimeout);
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
    if (audioManager_->isPlaying())
        stopAndReset();
    else {
        audioManager_->play();
        flashTimer_.start(500);
    }
}

void CartButton::stopAndReset(void)
{
    audioManager_->stop();
    flashTimer_.stop();
    redFlash_ = false;
    update();
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
        qint64 timeLeft = audioManager_->getAudioDuration() -
            audioManager_->getAudioPosition();

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
