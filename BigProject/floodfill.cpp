#include "floodfill.h"

FloodFill::FloodFill(Mat& img, Point seed, Scalar color, int tolerance, int connectivity)
{
    this->img = img;
    this->seed = seed;
    this->color = color;
    this->tolerance = tolerance;
    this->connectivity = connectivity;
    this->targetColor = img.at<Vec3b>(seed.y, seed.x);
    this->visited = vector<vector<bool>>(img.rows, vector<bool>(img.cols, false));
}

bool FloodFill::isColorMatch(Scalar pixelColor)
{
    double distance = norm(pixelColor,targetColor,NORM_INF);
    return distance <= tolerance;
}

void FloodFill::pushNeighborPixels(Point point)
{
    vector<Point> neighbors;
    if(connectivity == 4)
    {
        neighbors.push_back(Point(point.x + 1, point.y));
        neighbors.push_back(Point(point.x - 1, point.y));
        neighbors.push_back(Point(point.x, point.y + 1));
        neighbors.push_back(Point(point.x, point.y - 1));

    } else
    {
        neighbors.push_back(Point(point.x + 1, point.y));
        neighbors.push_back(Point(point.x - 1, point.y));
        neighbors.push_back(Point(point.x, point.y + 1));
        neighbors.push_back(Point(point.x, point.y - 1));
        neighbors.push_back(Point(point.x + 1, point.y + 1));
        neighbors.push_back(Point(point.x - 1, point.y - 1));
        neighbors.push_back(Point(point.x - 1, point.y + 1));
        neighbors.push_back(Point(point.x + 1, point.y - 1));
    }
    for(const auto& neighbor : neighbors)
    {
        if(neighbor.x >=0 && neighbor.x < img.cols && neighbor.y >=0 && neighbor.y < img.rows)
        {
            if(isColorMatch(img.at<Vec3b>(neighbor.y,neighbor.x)))
                q.push(neighbor);
        }
    }
}

void FloodFill::fill()
{
    q.push(seed);

    while(!q.empty())
    {
        Point current = q.front();
        q.pop();

        if(!visited[current.y][current.x] && isColorMatch(img.at<Vec3b>(current.y,current.x)))
        {
            visited[current.y][current.x] = true;
            Vec3b colorVec3b = Vec3b(color[0],color[1],color[2]);
            img.at<Vec3b>(current.y,current.x) = colorVec3b;
            pushNeighborPixels(current);
        }
    }

    /*if(seed.x <0 || seed.y < 0 || seed.x >= img.cols || seed.y >= img.rows)
        return;

    QStack<QPoint> points;
    points.push(QPoint(seed.x,seed.y));
    while(!points.empty())
    {
        QPoint diem = points.pop();
        int x = diem.x();
        int y = diem.y();
        if (img.at<uchar>(y,x) == color[0])
            continue;
        int x1=x;
        while (x1 <img.cols && abs(img.at<uchar>(y,x1) - img.at<uchar>(y,x)) <= tolerance)
        {
            img.at<uchar>(y,x1) = color[0];
            if(y > 0 && abs(img.at<uchar>(y-1,x1) - img.at<uchar>(y,x)) <= tolerance)
                points.push(QPoint(x1,y-1));
            if (y < img.rows - 1 && abs(img.at<uchar>(y + 1, x1) - img.at<uchar>(y, x)) <= tolerance)
                points.push(QPoint(x1, y + 1));

            ++x1;
        }
        --x1;
        while (x1 >= 0 && abs(img.at<uchar>(y, x1) - img.at<uchar>(y, x)) <= tolerance)
        {
            img.at<uchar>(y, x1) = color[0];
            if (y > 0 && abs(img.at<uchar>(y - 1, x1) - img.at<uchar>(y, x)) <= tolerance)
                points.push(QPoint(x1, y - 1));
            if (y < img.rows - 1 && abs(img.at<uchar>(y + 1, x1) - img.at<uchar>(y, x)) <= tolerance)
                points.push(QPoint(x1, y + 1));

            --x1;
        }
    }*/

}
void FloodFill::animateFill()
{
    int steps = 100;
    int stepSize = 80;


    for(int i=steps; i>0; i--)
    {
        Mat region = Mat::zeros(img.rows, img.cols, CV_8UC3);
        circle(region, seed, i*stepSize, Scalar(255,255,255), -1);

        Mat mask = Mat::zeros(img.rows, img.cols, CV_8UC1);
        threshold(region, mask, 1, 255, THRESH_BINARY);

        Mat subImage;
        img.copyTo(subImage,mask);
        fill();
        img = subImage;
        QImage qtImage = QImage((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888).rgbSwapped();
        waitKey(1);
    }
}
