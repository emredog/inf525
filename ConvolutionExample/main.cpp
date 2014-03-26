#include <QCoreApplication>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//#include <iostream>

using namespace cv;

//function decleration:
Mat convolveWithKernel(Mat img, Mat kernel, bool normalize);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    /// Declare variables
    Mat src, dst;

    Mat kernel;
    //Point anchor;
    //double delta;
    //int ddepth;
    int kernel_size;
    char* window_name = "Convolution Example";

    int c;

    /// Load an image
    src = imread( "/home/emredog/git/inf525/ConvolutionExample/Lenna-bw.png", CV_LOAD_IMAGE_GRAYSCALE /*argv[1] */);

    if( !src.data )
    { return -1; }


    QList<Mat> smoothingKernels;
    smoothingKernels.append(Mat::ones(3, 3, CV_8UC1));
    smoothingKernels.append(Mat::ones(5, 5, CV_8UC1));
    smoothingKernels.append(Mat::ones(7, 7, CV_8UC1));
    smoothingKernels.append(Mat::ones(9, 9, CV_8UC1));


    /// Create window
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );

    //Show original image
    Mat org = src.clone();
    putText(org, "Original Image", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, org );
    waitKey(0);

    //Smoothing kernels
    kernel = Mat::ones(3, 3, CV_8UC1);
    dst = convolveWithKernel(src, kernel, true);
    putText(dst, "3x3 Normalized Box Filter (Smoothing)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    kernel = Mat::ones(5, 5, CV_8UC1);
    dst = convolveWithKernel(src, kernel, true);
    putText(dst, "5x5 Normalized Box Filter (Smoothing)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    kernel = Mat::ones(7, 7, CV_8UC1);
    dst = convolveWithKernel(src, kernel, true);
    putText(dst, "7x7 Normalized Box Filter (Smoothing)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    kernel = Mat::ones(9, 9, CV_8UC1);
    dst = convolveWithKernel(src, kernel, true);
    putText(dst, "9x9 Normalized Box Filter (Smoothing)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    kernel = Mat::ones(11, 11, CV_8UC1);
    dst = convolveWithKernel(src, kernel, true);
    putText(dst, "11x11 Normalized Box Filter (Smoothing)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    //Show original image again
    imshow( window_name, org );
    waitKey(0);

    //Sharpen
    kernel = (Mat_<uchar>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    dst = convolveWithKernel(src, kernel, false);
    putText(dst, "3x3 Sharpening Filter", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    //Show original image again
    imshow( window_name, org );
    waitKey(0);

    //Edge detection
    kernel = (Mat_<uchar>(3,3) << 1, 0, -1, 0, 0, 0, -1, 0, 1);
    dst = convolveWithKernel(src, kernel, false);
    putText(dst, "3x3 Edge Detection Filter (1)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    //Show original image again
    imshow( window_name, org );
    waitKey(0);

    //Edge detection
    kernel = (Mat_<uchar>(3,3) << 0, 1, 0, 1, -4, 1, 0, 1, 0);
    dst = convolveWithKernel(src, kernel, false);
    putText(dst, "3x3 Edge Detection Filter (2)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);

    //Show original image again
    imshow( window_name, org );
    waitKey(0);

    //Edge detection
    kernel = (Mat_<uchar>(3,3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
    dst = convolveWithKernel(src, kernel, false);
    putText(dst, "3x3 Edge Detection Filter (3)", Point(15, 15), FONT_HERSHEY_PLAIN, 1, Scalar(255));
    imshow( window_name, dst );
    waitKey(0);





    return 0;

    //return a.exec();
}

//Convolve the image img with given kernel and returns new image
//Border condition: discard when you can't convolve
Mat convolveWithKernel(Mat img, Mat kernel, bool normalize)
{
    //kernel is assumed to be square (NxN kernel), N is odd
    assert(kernel.cols == kernel.rows);
    assert(kernel.cols % 2 == 1);

    //create new image with size and type of source image
    Mat result = Mat::zeros(img.size(), CV_8UC1);
    //    int type = img.type();

    int kernelSize = (kernel.rows-1)/2; //kernel size from center

    for (int r = kernelSize; r<img.rows-kernelSize; r++)
    {
        for (int c=kernelSize; c<img.cols-kernelSize; c++)
        {
            int sum = 0;
            int normalizationTerm = 0;

            // anchor is (r, c) point. we should perform a weighted average to its surrounding:
            for (int kr=0; kr<kernel.rows; kr++)
            {
                for (int kc=0; kc<kernel.cols; kc++)
                {
                    int termA = (int)img.at<uchar>(r - kernelSize + kr, c - kernelSize + kc);
                    int termB = (int)kernel.at<uchar>(kr, kc);
                    sum +=  termA * termB; //mutliply pixel value at (img_r, img_c) with kernel weight at (kr, kc) and add it to sum
                    normalizationTerm += kernel.at<uchar>(kr, kc); //for later use
                }
            }

            //set new value of (r, c)
            if (normalize && normalizationTerm != 0) //we should normalize by dividing the sum by norm. term
                sum /= normalizationTerm;

            uchar newVal = static_cast<uchar>(sum);
            result.at<uchar>(r, c) = newVal;
            //std::cout << "(" << r << ", " << c << ") : " << sum << "\n";
        }
    }

    return result;
}

//filter2D(src, dst, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
