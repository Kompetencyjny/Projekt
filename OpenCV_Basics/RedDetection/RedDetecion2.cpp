#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2\opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;

int main(int argc, char** argv) {
{
    Mat3b bgr = imread("C:/Users/Janek/Desktop/ImageProcessing/Plakietki/3.jpg");

    Mat3b bgr_inv = ~bgr;
    Mat3b hsv_inv;
    cvtColor(bgr_inv, hsv_inv, COLOR_BGR2HSV);

    Mat1b mask; 
    inRange(hsv_inv, Scalar(90 - 10, 70, 50), Scalar(90 + 10, 255, 255), mask); // Cyan is 90

    imshow("Mask", mask);
    waitKey();

    return 0;
}
}