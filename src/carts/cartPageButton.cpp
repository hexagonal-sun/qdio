#include <QDebug>
#include <QPainter>

#include "cartPageButton.h"

CartPageButton::CartPageButton(QWidget *parent, unsigned int pageNumber)
    : QAbstractButton(parent),
      redFlash_(false),
      noCartsPlaying_(0),
      pageNumber_(pageNumber)
{
    QFont widgetFont = font();

    widgetFont.setBold(true);
    widgetFont.setPointSize(widgetFont.pointSize() * 1.5);

    setFont(widgetFont);

    setText(QString::number(pageNumber + 1));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &CartPageButton::clicked,
            this, &CartPageButton::pageButtonClicked);

    connect(&flashTimer_, &QTimer::timeout, [=]
    {
        redFlash_ = !redFlash_;
        update();
    });
}

QSize CartPageButton::sizeHint() const
{
    QFontMetrics widgetFontInfo(font());

    return QSize(widgetFontInfo.width(text()) * 1.3,
                 widgetFontInfo.height() * 3);
}

QSize CartPageButton::minimumSizeHint() const
{
    QFontMetrics widgetFontInfo(font());

    return QSize(widgetFontInfo.width(text()),
                 widgetFontInfo.height() * 2);
}

void CartPageButton::cartPlaybackStarted()
{
    if (!noCartsPlaying_++)
        flashTimer_.start(500);
}

void CartPageButton::cartPlaybackStopped()
{
    if (!--noCartsPlaying_) {
        flashTimer_.stop();
        redFlash_ = false;
        update();
    }
}

void CartPageButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);

    if (redFlash_)
        painter.setBrush(Qt::red);

    // If this is the current page, don't bother showing a red flash.
    if(currentPage_)
        painter.setBrush(Qt::darkGreen);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 3));
    painter.drawRect(pe->rect());

    painter.drawText(pe->rect(), Qt::AlignCenter, text());
}

void CartPageButton::pageButtonClicked()
{
    if (!currentPage_) {
        emit pageChange(pageNumber_);
        currentPage_ = true;
    }
}

void CartPageButton::pageUpdate(int newPageNumber)
{
    if (newPageNumber == pageNumber_)
        currentPage_ = true;
    else
        currentPage_ = false;

    update();
}
