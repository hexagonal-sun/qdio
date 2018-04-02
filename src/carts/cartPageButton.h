#ifndef CARTPAGEBUTTON_H
#define CARTPAGEBUTTON_H

#include <QAbstractButton>
#include <QPaintEvent>
#include <QTimer>

class CartPageButton : public QAbstractButton
{
    Q_OBJECT
public:
    CartPageButton(QWidget *parent, unsigned int pageNumber);
signals:
    void pageChange(int newPageNumber);

public slots:
    void pageUpdate(int newPageNumber);
    void cartPlaybackStarted();
    void cartPlaybackStopped();

private slots:
    void pageButtonClicked();

private:
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    void paintEvent(QPaintEvent *pe);
    unsigned int pageNumber_;
    unsigned int noCartsPlaying_;
    bool currentPage_;
    bool redFlash_;
    QTimer flashTimer_;
};

#endif // CARTPAGEBUTTON_H
