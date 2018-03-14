#include "cartButton.h"
#include <QDebug>

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
