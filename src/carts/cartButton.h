#pragma once

#include <QAbstractButton>
#include <QMediaPlayer>
#include <QPaintEvent>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "cartAudioManager.h"

class CartButton : public QAbstractButton
{
    Q_OBJECT

public:
    CartButton(QWidget *parent, QString text, QString file);
    CartButton(QWidget *parent);
    void setCartTitle(const QString &text);

private slots:
    void flashTimeout();
    void clicked();

private:
    void setupAppearance(void);
    void paintEvent(QPaintEvent *event);
    void stopAndReset(void);
    const QString getCartText() const;
    const int calculateMinimumWidth() const;
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
    bool isReady(void) const;

    QTimer flashTimer_;
    bool redFlash_;
    CartAudioManager *audioManager_;

    enum {
        LOADING,
        EMPTY,
        ERROR,
        READY
    } cartState_;
};
