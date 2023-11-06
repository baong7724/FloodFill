#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void scaleSize(int& w, int& h) {
    int max_h = 321;
    int max_w = 551;
    if (double(h) / w <= double(max_h) / max_w) {
        h = h / double(w) * max_w - 1;
        w = max_w - 1;
    }
    else {
        w = w / double(h) * max_h - 1;
        h = max_h - 1;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.jpeg *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Open Images"),
                "",
                tr("Image Files (*.png *.jpeg *.jpg)"));
    if(!fileName.isEmpty())
    {
        String image_path = fileName.toLocal8Bit().constData();
        Mat image = imread(image_path);
        int c = image.cols;
        int r = image.rows;
        scaleSize(c,r);
        cv::resize(image,image,Size(c,r));;
        hide();
        mainWindow1 = new MainWindow1(this);
        mainWindow1->setImage(image,c,r);
        mainWindow1->show();
    }
}

