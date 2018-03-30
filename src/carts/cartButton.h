#pragma once

#include <QAbstractButton>
#include <QMediaPlayer>
#include <QPaintEvent>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "audioManager.h"

class CartButton : public QAbstractButton
{
    Q_OBJECT

public:
    CartButton(QWidget *parent, QString text, QString file, AudioManager *audioMan);
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
    qint64 duration_;
    qint64 position_;
    AudioManager *audioMan_;
    QMediaPlayer *mediaPlayer_;

    QTimer flashTimer_;
    bool redFlash_;

    enum {
        LOADING,
        EMPTY,
        ERROR,
        READY
    } cartState_;
};
