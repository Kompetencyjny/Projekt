#include "cv.hpp"

inline CV::CV()
{
	cap = VideoCapture(CAP_DSHOW);
	Sleep(1000);
	Mat imgTmp;
	cap.read(imgTmp);
}

inline char CV::colourDetector(int iLowH,int iHighH,int iLowS,int iHighS,int iLowV,int iHighV)
{

	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;
	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); 
		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream"<< endl;
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
			return 'a';
		}

		frame++;
		if (frame == 100)
		{
			frame = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}

	}
}

inline char CV::colourPicker()
{
	while (true) {
		if (colourDetector(0,11,112,255,108,255) == 'a') { //CZERWONY
			return 'a';
		}
		if (colourDetector(65,115,63,255,60,255) == 'a') { //NIEBIESKI
			return 'b';
		}
		if (colourDetector(15,36,130,255,105,255) == 'a') { //ZOLTY
			return 'c';
		}
		if (colourDetector(36,55,45,255,60,255) == 'a') { //ZIELONY
			return 'd';
		}
	}
}

