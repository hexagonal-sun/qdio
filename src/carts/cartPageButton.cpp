#include <QDebug>
#include <QPainter>

#include "cartPageButton.h"

CartPageButton::CartPageButton(QWidget *parent, unsigned int pageNumber)
    : QAbstractButton(parent),
      pageNumber_(pageNumber)
{
    QFont widgetFont = font();

    widgetFont.setBold(true);
    widgetFont.setPointSize(widgetFont.pointSize() * 1.5);

    setFont(widgetFont);

    setText(QString::number(pageNumber + 1));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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

void CartPageButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::green, 3));
    painter.drawRect(pe->rect());

    painter.drawText(pe->rect(), Qt::AlignCenter, text());
}
