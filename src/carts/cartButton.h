#pragma once

#include <QFileInfo>
#include <QAbstractButton>
#include <QColor>
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
    CartButton(QWidget *parent, QString text, QFileInfo file, AudioManager *audioMan,
               QColor textColour = Qt::white, QColor bgColour = Qt::darkBlue);
    CartButton(QWidget *parent);
    void setCartTitle(const QString &text);

signals:
    void cartPlaybackStrarted();
    void cartPlaybackStopped();

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
    QColor textColour_;
    QColor bgColour_;
    qint64 duration_;
    qint64 position_;
    AudioManager *audioMan_;
    QMediaPlayer *mediaPlayer_;
    QFileInfo cartFile_;

    QTimer flashTimer_;
    bool redFlash_;

    enum {
        LOADING,
        EMPTY,
        ERROR,
        READY
    } cartState_;
};
