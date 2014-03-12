#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

char* trackbar_type = "Threshold Type: \n 0: Binary \n 1: Binary Inverted";
char* trackbar_value_C = "C";
char* trackbar_adaptiveMethod = "Adaptive Method: \n 0: Mean \n 1: Gaussian";
char* trackbar_blockSize = "Block Size (2*bS + 1)";

int value_C = 0;
int threshold_type = 0;
int const max_value_C = 255;
int const max_type = 1;
int const max_BINARY_value = 255;

int adaptiveMethod = 0;
int blockSize = 1;
int max_blockSize = 49;

Mat frame;
Mat grayFrame, dst;

/// Function headers
void Threshold_Demo( int, void* );

int main(/*int argc, char *argv[]*/)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
            return -1;

    //create two displays
    namedWindow("original",1);
    namedWindow("modified",1);



    // Create Trackbars
     createTrackbar( trackbar_type, "modified", &threshold_type, max_type, 0 );
     createTrackbar( trackbar_value_C, "modified", &value_C, max_value_C, 0 );
     createTrackbar(trackbar_adaptiveMethod, "modified", &adaptiveMethod, 1, 0);
     createTrackbar(trackbar_blockSize, "modified", &blockSize, max_blockSize, 0);

     grayFrame = Mat::zeros(480, 640, CV_8UC1);

     // Call the function to initialize
     Threshold_Demo( 0, 0 );          


    for(;;)
    {
        cap >> frame; // get a new frame from camera
        cvtColor(frame, grayFrame, CV_RGB2GRAY);

        Threshold_Demo( 0, 0 );


        if(waitKey(30) >= 0) break;
    }
}

/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  adaptiveThreshold(grayFrame, dst, max_BINARY_value, adaptiveMethod, threshold_type, 2*blockSize+1, value_C);

  imshow("modified", dst );
  imshow("original", grayFrame); //display the image
}
