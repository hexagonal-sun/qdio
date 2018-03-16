#include <QPainter>

#include "controlButton.h"

ControlButton::ControlButton(QWidget *parent)
    : QPushButton(parent)
{
    QFont widgetFont = font();

    widgetFont.setBold(true);
    widgetFont.setPointSize(widgetFont.pointSize() * 1.5);

    setFont(widgetFont);
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}

void ControlButton::setText(const QString &text)
{
    QPushButton::setText("\n" + text + "\n");
}

void ControlButton::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    QPen pen(Qt::yellow, 3);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);
    painter.setBrush(Qt::red);
    painter.drawRect(pe->rect());

    painter.drawText(pe->rect(), Qt::AlignCenter, text());
}
