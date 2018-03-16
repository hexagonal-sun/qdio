#ifndef CONTROLBUTTON_H
#define CONTROLBUTTON_H

#include <QPushButton>
#include <QPaintEvent>

class ControlButton : public QPushButton
{
public:
    ControlButton(QWidget *parent);
    void setText(const QString &text);
private:
    void paintEvent(QPaintEvent *pe);
};

#endif // CONTROLBUTTON_H
