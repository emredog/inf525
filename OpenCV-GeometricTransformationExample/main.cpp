#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(/*int argc, char *argv[]*/)
{
    //QCoreApplication a(argc, argv);

    //load image in grayscale
    Mat image = imread("/home/emredog/Pictures/lenna.jpg", CV_LOAD_IMAGE_GRAYSCALE);
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

    //scale image---------------------------------------------------------------------------
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


    //scale & rotate image---------------------------------------------------------------------------
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


    //skew image---------------------------------------------------------------------------
    Mat skewed;
    // exemple of 2 triangles (3 vertex and 1 gravity center points per triangle)
    int aX = 15, aY = 0; // CHANGE THESE VALUES

    Point2f srct[4];
    srct[0] = Point2f(0, 0);
    srct[1] = Point2f(300, 600);
    srct[2] = Point2f(50, 700);
    srct[3] = Point2f(110, 430);

    Point2f dstt[4];
    dstt[0] = cv::Point2f(0, 0); // NEW POINT TO PLACE srct[0]
    dstt[1] = cv::Point2f(300 + aX, 600 + aY);
    dstt[2] = cv::Point2f(50 + aX < 0 ? 0 : 50 + aX, 700 + aY);

    dstt[0].x = dstt[0].x < 0 ? 0 : (dstt[0].x >= image.cols + aX ? image.cols + aX - 1 : dstt[0].x);
    dstt[1].x = dstt[1].x < 0 ? 0 : (dstt[1].x >= image.cols + aX ? image.cols + aX - 1 : dstt[1].x);
    dstt[2].x = dstt[2].x < 0 ? 0 : (dstt[2].x >= image.cols + aX ? image.cols + aX - 1 : dstt[2].x);

    dstt[0].y = dstt[0].y < 0 ? 0 : (dstt[0].y >= image.rows + aY ? image.rows + aY - 1 : dstt[0].y);
    dstt[1].y = dstt[1].y < 0 ? 0 : (dstt[1].y >= image.rows + aY ? image.rows + aY - 1 : dstt[1].y);
    dstt[2].y = dstt[2].y < 0 ? 0 : (dstt[2].y >= image.rows + aY ? image.rows + aY - 1 : dstt[2].y);

    dstt[3] = Point2f((dstt[0].x + dstt[1].x + dstt[2].x) / 3, (dstt[0].y + dstt[1].y + dstt[2].y) / 3); // new gravity center

    Mat transformMat = getPerspectiveTransform(srct, dstt);
    std::cout << std::endl << std::endl << transformMat << std::endl << std::endl;

    //nearest neighbor
    warpPerspective(image, skewed, transformMat, cv::Size(image.cols + aX, image.rows + aY), INTER_NEAREST);
    putText(skewed, "nearest-neighbor interpolation", Point(10, 400), fontFace, fontScale, color, thickness);
    imshow("transformed", skewed);
    cv::waitKey();
    //bilinear
    warpPerspective(image, skewed, transformMat, cv::Size(image.cols + aX, image.rows + aY), INTER_LINEAR);
    putText(skewed, "bilinear interpolation", Point(10, 400), fontFace, fontScale, color, thickness);
    imshow("transformed", skewed);
    cv::waitKey();
    //bicubic
    warpPerspective(image, skewed, transformMat, cv::Size(image.cols + aX, image.rows + aY), INTER_CUBIC);
    putText(skewed, "bicubic interpolation", Point(10, 400), fontFace, fontScale, color, thickness);
    imshow("transformed", skewed);
    cv::waitKey();



    //return a.exec();
}
