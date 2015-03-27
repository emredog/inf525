#include <QCoreApplication>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(/*int argc, char *argv[]*/)
{
    double alpha = 1.2;
    double beta = 100;

    //read image from disk
    Mat origImg = imread("/home/emredog/Pictures/lenna.jpg");

    //create a zero-matrix with original image size & type
    Mat modifiedImg = Mat::zeros( origImg.size(), origImg.type() );

    // Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for( int y = 0; y < origImg.rows; y++ ) //traverse rows
    {
        for( int x = 0; x < origImg.cols; x++ ) //traverse columns
        {
            for( int c = 0; c < 3; c++ ) //traverse RGB channels
            {
                // What difference saturate_cast make?
                modifiedImg.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alpha*( origImg.at<Vec3b>(y,x)[c] ) + beta );
//                modifiedImg.at<Vec3b>(y,x)[c] = alpha*( origImg.at<Vec3b>(y,x)[c] ) + beta;
            }
        }
    }

    //create an empty matrix
    Mat convertedImg;
    //easy way to do the same operation
    origImg.convertTo(convertedImg, -1, alpha, beta);

    //create three windows to show images
    namedWindow("org", 1);
    namedWindow("converted", 1);
    namedWindow("manually_modified", 1);

    //verify output images are equal
    Mat resultMask = (convertedImg == modifiedImg);
    for (int y=0; y<resultMask.rows; y++)
        for (int x=0; x<resultMask.cols; x++)
            if (resultMask.at<uchar>(y, x) != 255)
            {
                std::cout << "IMAGES NOT EQUAL" << std::endl;
                break;
            }

    //show images
    imshow("org", origImg);
    imshow("manually_modified", modifiedImg);
    imshow("converted", convertedImg);
    cv::waitKey();
    return 0;
}
