#include "cv.hpp"

static VideoCapture cap(0);

inline char CV::colourPicker()
{
	while (true) {
		if (colourDetector() == 'a') { //CZERWONY
			return 'a';
		}
		if (colourDetector() == 'b') { //NIEBIESKI
			return 'b';
		}
		if (colourDetector() == 'c') { //ZOLTY
			return 'c';
		}
		if (colourDetector() == 'd') { //ZIELONY
			return 'd';
		}
	}
}

inline char CV::colourDetector()
{
	Sleep(1000);
	Mat imgTmp;
	cap.read(imgTmp);
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;
	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal);
		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		Mat imgHSV;
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
		Mat imgThresholded1;
		inRange(imgHSV, Scalar(65, 115, 63), Scalar(255, 60, 255), imgThresholded1); //BLUE
		erode(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded1, imgThresholded1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		counter = countNonZero(imgThresholded1);
		if (counter > 6000)
		{
			return 'b';
		}

		Mat imgThresholded2;
		inRange(imgHSV, Scalar(0, 11, 112), Scalar(255, 108, 255), imgThresholded2); //RED
		erode(imgThresholded2, imgThresholded2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded2, imgThresholded2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded2, imgThresholded2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded2, imgThresholded2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		counter = countNonZero(imgThresholded2);
		if (counter > 6000)
		{
			return 'a';
		}

		Mat imgThresholded3;
		inRange(imgHSV, Scalar(15, 36, 130), Scalar(255, 105, 255), imgThresholded3); //YELLOW
		erode(imgThresholded3, imgThresholded3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded3, imgThresholded3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded3, imgThresholded3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded3, imgThresholded3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		counter = countNonZero(imgThresholded3);
		if (counter > 6000)
		{
			return 'c';
		}

		Mat imgThresholded4;
		inRange(imgHSV, Scalar(36, 55, 45, 255), Scalar(255, 60, 255), imgThresholded4); //GREEN
		erode(imgThresholded4, imgThresholded4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded4, imgThresholded4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded4, imgThresholded4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded4, imgThresholded4, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		counter = countNonZero(imgThresholded4);
		if (counter > 6000)
		{
			return 'd';
		}
	}
}
