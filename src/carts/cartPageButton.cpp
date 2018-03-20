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

    connect(this, &CartPageButton::clicked,
            this, &CartPageButton::pageButtonClicked);
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

    if (currentPage_)
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
