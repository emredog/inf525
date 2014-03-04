#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>


using namespace cv;

int main(/*int argc, char *argv[]*/)
{
    //QCoreApplication a(argc, argv);

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    Mat transformed;
    Mat frame;
    Mat frame2;
   // namedWindow("edges",1);
    namedWindow("original",1);

    Mat transformMat = getRotationMatrix2D(Point2f(240, 320), 180.0, 1.0);
    for(;;)
    {

        cap >> frame; // get a new frame from camera

       // cvtColor(frame, frame2, CV_);
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        transform(frame, transformed, transformMat);
        imshow("original", transformed);
        if(waitKey(30) >= 0) break;
    }

    //return a.exec();
}
