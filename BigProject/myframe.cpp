#include "myframe.h"

MyFrame::MyFrame(QWidget *parent) : QFrame(parent)
{
}

void MyFrame::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        emit clicked();
    }
    QFrame::mousePressEvent(event);
}

