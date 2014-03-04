#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(/*int argc, char *argv[]*/)
{
    double alpha = 1.0;
    double beta = 100;

    Mat origImg = imread("/home/emredog/Pictures/Lenna.png");
    Mat modifiedImg, convertedImg;

    namedWindow("org", 1);
    namedWindow("new", 1);
    namedWindow("converted", 1);

    modifiedImg = origImg*alpha + beta;
    origImg.convertTo(convertedImg, -1, alpha, beta);

    imshow("org", origImg);
    imshow("new", modifiedImg);
    imshow("converted", convertedImg);
    cv::waitKey();
    return 0;
}
