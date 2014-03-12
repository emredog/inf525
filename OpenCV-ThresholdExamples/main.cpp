#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

int threshold_value = 0;
int threshold_type = 3;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

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



    // Create Trackbar to choose type of Threshold
     createTrackbar( trackbar_type,
                     "modified", &threshold_type,
                     max_type, Threshold_Demo );

     createTrackbar( trackbar_value,
                     "modified", &threshold_value,
                     max_value, Threshold_Demo );

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

  threshold( grayFrame, dst, threshold_value, max_BINARY_value,threshold_type );

  imshow( "modified", dst );
  imshow("original", grayFrame); //display the image
}
