#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(/*int argc, char *argv[]*/)
{
    //QCoreApplication a(argc, argv);

    //load image in grayscale
    Mat image = imread("/home/emredog/Pictures/Lenna.png", CV_LOAD_IMAGE_GRAYSCALE);
    //create window to show image
    namedWindow("original", 1);
    imshow("original", image);
    cv::waitKey(); //press key to continue

    //create a second window
    namedWindow("transformed", 1);
    //some visual parameters:
    int fontFace = FONT_HERSHEY_PLAIN;
    double fontScale = 1.4;
    Scalar color(255, 255, 255);
    int thickness = 2;

    //scale image
    double scaleFactor = 1.4;
    Mat scaled;
    //nearest neighbor
    resize(image, scaled, Size(0,0), scaleFactor, scaleFactor, INTER_NEAREST);
    putText(scaled, "nearest-neighbor interpolation", Point(10, scaled.rows-5), fontFace, fontScale, color, thickness);
    imshow("transformed", scaled);
    cv::waitKey();

    //bilinear
    resize(image, scaled, Size(0,0), scaleFactor, scaleFactor, INTER_LINEAR);
    putText(scaled, "bilinear interpolation", Point(10, scaled.rows-5), fontFace, fontScale, color, thickness);
    imshow("transformed", scaled);
    cv::waitKey();

    //bicubic
    resize(image, scaled, Size(0,0), scaleFactor, scaleFactor, INTER_CUBIC);
    putText(scaled, "bicubic interpolation", Point(10, scaled.rows-5), fontFace, fontScale, color, thickness);
    imshow("transformed", scaled);
    cv::waitKey();

//    //translate image
    //TODO

    //scale & rotate image
    Mat rotated = Mat::zeros(image.rows, image.cols, image.type());
    Point center(image.cols/2, image.rows/2);
    double angle = 30.0;
    scaleFactor = 1.0;
    Size destinationSize(image.rows, image.cols);
    Mat rotationMat = getRotationMatrix2D(center, angle, scaleFactor);
    std::cout << rotationMat << std::endl << std::endl ;

    //nearest neighbor
    warpAffine(image, rotated, rotationMat, destinationSize, INTER_NEAREST);
    putText(rotated, "nearest-neighbor interpolation", Point(10, 400), fontFace, fontScale, color, thickness);
    imshow("transformed", rotated);
    cv::waitKey();

    //bilinear
    warpAffine(image, rotated, rotationMat, destinationSize, INTER_LINEAR);
    putText(rotated, "bilinear interpolation", Point(10, 400), fontFace, fontScale, color, thickness);
    imshow("transformed", rotated);
    cv::waitKey();

    //bicubic
    warpAffine(image, rotated, rotationMat, destinationSize, INTER_CUBIC);
    putText(rotated, "bicubic-neighbor interpolation", Point(10, 400), fontFace, fontScale, color, thickness);
    imshow("transformed", rotated);
    cv::waitKey();


    //skew image







    //return a.exec();
}
