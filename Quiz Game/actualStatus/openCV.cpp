#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>
#include <time.h>

using namespace cv;
using namespace std;

int tester=0;
int counter = 0;


char redDetect()
{
	VideoCapture cap(0); 
	int iLowH = 0;
	int iHighH = 11;
	int iLowS = 112;
	int iHighS = 255;
	int iLowV = 108;
	int iHighV = 255;

	Mat imgTmp;
	cap.read(imgTmp);

	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); 



		if (!bSuccess) 
		{
			cout << "Cannot read a frame from video stream RED" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); 

		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			destroyAllWindows();
			cap.release();
			return 'a';

		}
		
		tester++;
		if (tester == 20)
		{
			tester = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}



char blueDetect()
{
	VideoCapture cap(0); 
	int iLowH = 65;
	int iHighH = 115;
	int iLowS = 63;
	int iHighS = 255;
	int iLowV = 60;
	int iHighV = 255;

	Mat imgTmp;
	cap.read(imgTmp);

	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); 



		if (!bSuccess) 
		{
			cout << "Cannot read a frame from video stream Blue" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); 

		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			cap.release();
			destroyAllWindows();
			return 'c';
		}

		tester++;
		if (tester == 20)
		{
			tester = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}



char greenDetect()
{
	VideoCapture cap(0); 
	int iLowH = 36;
	int iHighH = 55;
	int iLowS = 45;
	int iHighS = 255;
	int iLowV = 60;
	int iHighV = 255;

	Mat imgTmp;
	cap.read(imgTmp);

	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); 



		if (!bSuccess) 
		{
			cout << "Cannot read a frame from video stream GREEN" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
								 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			cap.release();
			destroyAllWindows();
			return 'd';
		}

		tester++;
		if (tester == 20)
		{
			tester = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}



char yellowDetect()
{
	VideoCapture cap(0);
	int iLowH = 15;
	int iHighH = 36;
	int iLowS = 130;
	int iHighS = 255;
	int iLowV = 105;
	int iHighV = 255;

	Mat imgTmp;
	cap.read(imgTmp);
	
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); 



		if (!bSuccess) 
		{
			cout << "Cannot read a frame from video stream YELLOW" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); 

		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			cap.release();
			destroyAllWindows();
			return 'b';
		}

		tester++;
		if (tester == 20)
		{
			tester = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}
char colourChooser() {
	//a - czerwony
	//b - zolty
	//c - niebieski
	//d - zielony
	while ((redDetect() == 'e' && yellowDetect() == 'e'&& blueDetect() == 'e'&& greenDetect() == 'e')) {
		if (redDetect() == 'a') {
			return 'a';
		}
		if (yellowDetect() == 'b') {
			return 'b';
		}
		if (blueDetect() == 'c') {
			return 'c';
		}
		if (greenDetect() == 'd') {
			return 'd';
		}
	}
}