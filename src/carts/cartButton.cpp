#include "cartButton.h"
#include <QDebug>
#include <QPainter>

CartButton::CartButton(QWidget *parent, QString text, QString file)
    : QAbstractButton(parent),
      cartFile(file),
      currentPosition_(0),
      redFlash_(false)
{
    player_.setNotifyInterval(100);

    setText(text);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &QAbstractButton::released, this, &CartButton::clicked);

    connect(&player_, &QMediaPlayer::positionChanged,
            this, &CartButton::positionUpdate);

    connect(&flashTimer_, &QTimer::timeout,
            this, &CartButton::flashTimeout);

    connect(&player_, &QMediaPlayer::durationChanged,
            this, &CartButton::durationUpdate);

    player_.setMedia(QUrl::fromLocalFile("/Users/matthew/test.mp3"));
}

void CartButton::clicked()
{
    if (player_.state() == QMediaPlayer::StoppedState) {
        player_.play();
        flashTimer_.start(500);
    } else {
        player_.stop();
        flashTimer_.stop();
        redFlash_ = false;
    }
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
    QFont font = painter.font();
    auto bgColour = isEnabled() ? Qt::darkBlue : Qt::black;
    auto txtColour = isEnabled() ? Qt::white : Qt::gray;

    if (redFlash_)
        bgColour = Qt::red;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(bgColour);
    painter.drawRect(pe->rect());

    painter.setPen(QPen(txtColour));
    font.setBold(true);
    font.setPointSize(font.pointSize() * 1.5);
    painter.setFont(font);

    painter.drawText(pe->rect(), Qt::AlignCenter, getCartText());
}
