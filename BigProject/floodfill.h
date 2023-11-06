#ifndef FLOODFILL_H
#define FLOODFILL_H

#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <queue>
#include <vector>
#include <QImage>
#include <QPixmap>
#include <QStack>
#include <QPoint>

using namespace std;
using namespace cv;

class FloodFill
{
public:
    FloodFill(Mat& img, Point seed, Scalar color, int tolerance, int connectivity);
    virtual void fill();
    virtual void animateFill();

protected:
    Mat img;
    Point seed;
    Scalar color;
    int tolerance;
    int connectivity;
    Scalar targetColor;
    queue <Point> q;
    vector <vector<bool>> visited;
    bool isColorMatch(Scalar pixelColor);
    void pushNeighborPixels(Point point);

};

#endif // FLOODFILL_H
