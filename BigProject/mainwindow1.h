#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <QPixmap>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>
#include <QLabel>
#include <QtCore>
#include <QTimer>
#include <QFileDialog>
#include "dialog.h"
#include <QStack>
#include <vector>
#include <queue>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow1;
}

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();
    void setImage(const Mat &image, int c, int r);
    int m_x, m_y;
    QColor color;
    Mat imge;
    bool checked;
    Dialog *dialog;

private slots:
    void on_pushButton_clicked();
    void change_pixel_pos(QPoint& pos);
    void on_pushButton_7_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::MainWindow1 *ui;
    QImage originalImage;
    QStack<QImage> undoStack;
    QStack<QImage> redoStack;
};

#endif // MAINWINDOW1_H
