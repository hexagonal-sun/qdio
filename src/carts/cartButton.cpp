#include "cartButton.h"
#include <QDebug>
#include <QPainter>

CartButton::CartButton(QWidget *parent, QString text, QString file)
    : QPushButton(text, parent),
      cartTitle_(text),
      cartFile(file)
{
    player_.setNotifyInterval(100);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &QPushButton::released, this, &CartButton::clicked);

    connect(&player_, &QMediaPlayer::positionChanged,
            this, &CartButton::positionUpdate);
}

void CartButton::clicked()
{
    if (player_.state() == QMediaPlayer::StoppedState) {
        player_.setMedia(QUrl::fromLocalFile("/home/matthew/test.mp3"));
        player_.play();
    } else {
        player_.stop();
        setText(cartTitle_);
    }
}

void CartButton::positionUpdate(qint64 newpos)
{
    setText(QString::number(newpos));
}

void CartButton::setCartTitle(const QString &text)
{
    setText(text);
    cartTitle_ = text;
}

void CartButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    QFont font = painter.font();
    auto bgColour = isEnabled() ? Qt::darkBlue : Qt::black;
    auto txtColour = isEnabled() ? Qt::white : Qt::gray;
    QString displayText = isEnabled() ? text() : "Empty";

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 3));
    painter.setBrush(bgColour);
    painter.drawRect(pe->rect());

    painter.setPen(QPen(txtColour));
    font.setBold(true);
    font.setPointSize(font.pointSize() * 1.5);
    painter.setFont(font);

    painter.drawText(pe->rect(), Qt::AlignCenter, displayText);
}
