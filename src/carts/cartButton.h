#pragma once

#include <QAbstractButton>
#include <QMediaPlayer>
#include <QPaintEvent>
#include <QString>
#include <QTimer>
#include <QWidget>

class CartButton : public QAbstractButton
{
    Q_OBJECT

public:
    CartButton(QWidget *parent, QString text, QString file);
    void setCartTitle(const QString &text);

private slots:
    void clicked();
    void positionUpdate(qint64 pos);
    void flashTimeout();
    void durationUpdate(qint64 newDuration);
    const QString getCartText() const;

private:
    void paintEvent(QPaintEvent *event);
    void stop();

    QMediaPlayer player_;
    QString cartFile;
    QTimer flashTimer_;
    qint64 cartDuration_;
    qint64 currentPosition_;
    bool redFlash_;
};
