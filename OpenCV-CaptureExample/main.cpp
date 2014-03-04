#include <QCoreApplication>
#include <QTime>
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

    int counter = 0;
    Mat frame;

    namedWindow("original",1);

    for(;;counter++)
    {

        cap >> frame; // get a new frame from camera

        imshow("original", frame); //display the image

        //save every 50th image to disk
        if (counter % 50 == 0)
        {
            std::string fileName = QTime::currentTime().toString("hh-mm-ss-zzz").append(".png").toStdString();
            imwrite(fileName, frame);
        }

        if(waitKey(30) >= 0) break;
    }

    //return a.exec();
}
