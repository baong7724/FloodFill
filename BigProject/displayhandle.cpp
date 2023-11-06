#include "displayhandle.h"
#include <queue>
#include <utility>
using namespace std;

int max_h = 321;
int max_w = 551;

displayhandle::displayhandle(QWidget* parent): QLabel(parent)
{
    this->setMouseTracking(true);
}

void displayhandle::mousePressEvent(QMouseEvent *mouseE)
{
    QPoint mouse_pos = mouseE->pos();
    if(mouseE->button() == Qt::LeftButton)
        if(mouse_pos.x() <= this->size().width() && mouse_pos.y() <= this->size().height() && mouse_pos.x() > 0 && mouse_pos.y() > 0){
            emit sendMousePosition(mouse_pos);
    }
}
void displayhandle::changeRect(int w, int h)
{
    int x=(max_w-w)/2;
    int y=(max_h-h)/2;
    this->setGeometry(x,y+25,w,h);
}

void displayhandle::setPic(Mat &image)
{
    QImage dest = QImage((const uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
    setPixmap(QPixmap::fromImage(dest.scaled(image.cols,image.rows,Qt::KeepAspectRatioByExpanding)));
}
