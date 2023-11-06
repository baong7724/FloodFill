#ifndef MYFRAME_H
#define MYFRAME_H

#include <QFrame>
#include <QMouseEvent>

class MyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit MyFrame(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MYFRAME_H
