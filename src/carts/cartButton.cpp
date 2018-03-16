#include "cartButton.h"
#include <QDebug>
#include <QPainter>

CartButton::CartButton(QWidget *parent, QString text, QString file)
    : QAbstractButton(parent),
      cartFile(file),
      currentPosition_(0),
      redFlash_(false)
{
    QFont widgetFont = font();

    widgetFont.setBold(true);
    widgetFont.setPointSize(widgetFont.pointSize() * 1.5);

    setFont(widgetFont);

    setText(text);

    player_.setNotifyInterval(100);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &QAbstractButton::released, this, &CartButton::clicked);

    connect(&player_, &QMediaPlayer::positionChanged,
            this, &CartButton::positionUpdate);

    connect(&flashTimer_, &QTimer::timeout,
            this, &CartButton::flashTimeout);

    connect(&player_, &QMediaPlayer::durationChanged,
            this, &CartButton::durationUpdate);

    connect(&player_, &QMediaPlayer::mediaStatusChanged,
            this, &CartButton::mediaStatusChanged);

    player_.setMedia(QUrl::fromLocalFile("/Users/matthew/test.mp3"));
}

void CartButton::mediaStatusChanged(const QMediaPlayer::MediaStatus newStatus)
{
    if (newStatus == QMediaPlayer::EndOfMedia)
        stop();
}

void CartButton::stop()
{
    player_.stop();
    flashTimer_.stop();
    currentPosition_ = 0;
    redFlash_ = false;
}

const int CartButton::calculateMinimumWidth() const
{
    QFontMetrics widgetFontMetrics(font());

    if (!isEnabled())
       return widgetFontMetrics.width("Empty");

    return widgetFontMetrics.width(text());
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
    int minimumWidth = widgetFontInfo.width(text());

    return QSize(calculateMinimumWidth(),
                 widgetFontInfo.height() * 3);
}

void CartButton::clicked()
{
    if (player_.state() == QMediaPlayer::StoppedState) {
        player_.play();
        flashTimer_.start(500);
    } else
        stop();
}

void CartButton::positionUpdate(qint64 newpos)
{
    currentPosition_ = newpos;

    update();
}

void CartButton::flashTimeout()
{
    redFlash_ = !redFlash_;
}

void CartButton::durationUpdate(qint64 newDuration)
{
    cartDuration_ = newDuration;

    update();
}

const QString CartButton::getCartText() const
{
    qint64 timeLeft = cartDuration_ - currentPosition_;
    QString ret;

    if (!isEnabled())
        return "Empty";

    ret.sprintf("%s\n\n%0.1f", text().toStdString().c_str(), (double)timeLeft / 1000);

    return ret;
}

void CartButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    auto bgColour = isEnabled() ? Qt::darkBlue : Qt::black;
    auto txtColour = isEnabled() ? Qt::white : Qt::gray;

    if (redFlash_)
        bgColour = Qt::red;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(bgColour);
    painter.drawRect(pe->rect());

    painter.setPen(QPen(txtColour));

    painter.drawText(pe->rect(), Qt::AlignCenter, getCartText());
}
