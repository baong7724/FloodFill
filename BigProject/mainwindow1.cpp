#include "mainwindow1.h"
#include "ui_mainwindow1.h"
#include "floodfill.h"
#include "displayhandle.h"

void scaleSizee(int& w, int& h) {
    int max_hi = 321;
    int max_wi = 551;
    if (double(h) / w <= double(max_hi) / max_wi) {
        h = h / double(w) * max_wi - 1;
        w = max_wi - 1;
    }
    else {
        w = w / double(h) * max_hi - 1;
        h = max_hi - 1;
    }
}

MainWindow1::MainWindow1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow1)
{
    ui->setupUi(this);
    m_x=m_y=0;
    checked = false;
    connect(ui->img, SIGNAL(sendMousePosition(QPoint&)), this, SLOT(change_pixel_pos(QPoint&)));
}
void MainWindow1::setImage(const Mat &image, int c, int r)
{
    QImage dest((const uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
    ui->img->setPixmap(QPixmap::fromImage(dest.scaled(image.cols,image.rows,Qt::KeepAspectRatioByExpanding)));
    ui->img->changeRect(c, r);
    originalImage = ui->img->pixmap().toImage();
    imge = image.clone();
    undoStack.push(ui->img->pixmap().toImage());
}

MainWindow1::~MainWindow1()
{
    delete ui;
}

void MainWindow1::on_pushButton_clicked()
{
    color = QColorDialog::getColor(Qt::white, this, "Choose Color");
}

void MainWindow1::change_pixel_pos(QPoint &pos)
{
    if(checked){
        m_x=pos.x();
        m_y=pos.y();
        Point seed = Point(m_x,m_y);
        Scalar cvColor(color.blue(), color.green(), color.red());
        QString spin = ui->spinBox->text();
        QString spin_2 = ui->spinBox_2->text();
        int tolerance = spin.toInt();
        int connectivity = spin_2.toInt();
        undoStack.push(ui->img->pixmap().toImage());
        redoStack.clear();
        FloodFill *floodfill = new FloodFill(imge,seed,cvColor,tolerance,connectivity);
        floodfill->animateFill();
        QImage currentImage = QImage((uchar*)imge.data, imge.cols, imge.rows, imge.step, QImage::Format_BGR888).rgbSwapped();
        ui->img->setPic(imge);
    }
}

void MainWindow1::on_pushButton_7_clicked()
{
    if(!checked && !imge.empty()) {
        checked=true;
        ui->img->setCursor(QCursor(QPixmap(":/img/img/brush.cur"),0,0));
    }
    else {
        ui->img->setCursor(QCursor(Qt::ArrowCursor));
        checked=false;
    }
}


void MainWindow1::on_pushButton_2_clicked()
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
        scaleSizee(c,r);
        cv::resize(image,image,Size(c,r));;
        QImage dest((const uchar*) image.data, image.cols, image.rows, image.step, QImage::Format_BGR888);
        ui->img->setPixmap(QPixmap::fromImage(dest.scaled(image.cols,image.rows,Qt::KeepAspectRatioByExpanding)));
        ui->img->changeRect(c, r);
        undoStack.push(ui->img->pixmap().toImage());
        imge = image.clone();

    }

}
void MainWindow1::on_pushButton_6_clicked()
{

    Mat imae = imge.clone();
    QString myNum;
    long long rVal=rand()%1929293;
    myNum = QString::number(rVal);
    QString path = "C:/Users/admin/Pictures/output_image"+myNum+".jpg";
    cv::imwrite(path.toStdString(),imae);
    dialog = new Dialog(this);
    dialog->show();
}


void MainWindow1::on_pushButton_4_clicked()
{
    if(!undoStack.isEmpty())
    {
        redoStack.push(ui->img->pixmap().toImage());
        QImage previousImage = undoStack.pop();
        ui->img->setPixmap(QPixmap::fromImage(previousImage));
    }
    else
    {
        ui->img->setPixmap(QPixmap::fromImage(originalImage));

    }
}

void MainWindow1::on_pushButton_5_clicked()
{
    if(!redoStack.isEmpty())
    {
        undoStack.push(ui->img->pixmap().toImage());
        QImage nextImage = redoStack.pop();
        ui->img->setPixmap(QPixmap::fromImage(nextImage));
    }
    else
    {
        ui->img->setPixmap(QPixmap::fromImage(originalImage));

    }
}

