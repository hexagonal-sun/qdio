#ifndef CARTPAGEBUTTON_H
#define CARTPAGEBUTTON_H

#include <QAbstractButton>
#include <QPaintEvent>

class CartPageButton : public QAbstractButton
{
public:
    CartPageButton(QWidget *parent, unsigned int pageNumber);
private:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *pe);
    unsigned int pageNumber_;
};

#endif // CARTPAGEBUTTON_H
