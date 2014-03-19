#include <QCoreApplication>
#include <QVector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;

void plotHistogramGrayscale(Mat image);

int main(int argc, char *argv[])
{
    Mat img = imread("/home/emredog/Lenna-bw.png");
    plotHistogramGrayscale(img);
}

void plotHistogramGrayscale(Mat image)
{
    Mat dst;
    if (image.channels() > 1)
        cvtColor(image, dst, CV_BGR2GRAY);
    else
        dst = image;

    //calculate histogram
    QVector<int> histogram(256, 0);

    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            // Get a pixel value [0-255]
            int pixelValue = dst.at<uchar>(i, j);
            histogram[pixelValue] ++;  // Update histogram value
        }
    }

    QVector<int>::iterator it = std::max_element(histogram.begin(), histogram.end());
    int max = *it;

    int histHeight = 500;
    float scale = (float)histHeight / (float)(dst.rows * dst.cols);
    Mat histImg = Mat::zeros(histHeight, 256, CV_8UC1);

    for( int h = 0; h < 256; h++ )
    {
        float intensity = histogram[h];
        intensity = (intensity/max)*256;

        line(histImg, Point(h, intensity), Point(h, 0), 255);
    }

    namedWindow( "Source", 1 );
    imshow( "Source", dst );

    namedWindow( "H-S Histogram", 1 );
    imshow( "H-S Histogram", histImg );
    waitKey(0);
}
