#pragma once

#include <QPushButton>
#include <QMediaPlayer>
#include <QPaintEvent>
#include <QString>
#include <QTimer>
#include <QWidget>

class CartButton : public QPushButton
{
    Q_OBJECT

public:
    CartButton(QWidget *parent, QString text, QString file);
    void setCartTitle(const QString &text);

private slots:
    void clicked();
    void positionUpdate(qint64 pos);
    void flashTimeout();

private:
    void paintEvent(QPaintEvent *event);
    QMediaPlayer player_;
    QString cartFile;
    QString cartTitle_;
    QTimer flashTimer_;
    qint64 currentPosition_;
    bool redFlash_;
};
