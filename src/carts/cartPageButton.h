#ifndef CARTPAGEBUTTON_H
#define CARTPAGEBUTTON_H

#include <QAbstractButton>
#include <QPaintEvent>

class CartPageButton : public QAbstractButton
{
    Q_OBJECT
public:
    CartPageButton(QWidget *parent, unsigned int pageNumber);
signals:
    void pageChange(int newPageNumber);

public slots:
    void pageUpdate(int newPageNumber);

private slots:
    void pageButtonClicked();

private:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *pe);
    unsigned int pageNumber_;
    bool currentPage_;
};

#endif // CARTPAGEBUTTON_H
