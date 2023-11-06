#ifndef DISPLAYHANDLE_H
#define DISPLAYHANDLE_H
#include <opencv2/opencv.hpp>
#include <QLabel>
#include <QMouseEvent>

using namespace cv;

extern int max_w, max_h;

class displayhandle : public QLabel
{
    Q_OBJECT
public:
    displayhandle(QWidget* parent=0);

    void setPic(Mat &image);
    void changeRect(int w, int h);

protected:
    void mousePressEvent(QMouseEvent * mouseE);

signals:
    void sendMousePosition(QPoint&);
};

#endif // DISPLAYHANDLE_H
