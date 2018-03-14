#pragma once

#include <QPushButton>
#include <QMediaPlayer>
#include <QString>
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

private:
    QMediaPlayer player_;
    QString cartFile;
    QString cartTitle_;
};
