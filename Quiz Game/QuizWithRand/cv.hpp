#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "windows.h"

using namespace cv;
using namespace std;

class CV
{
public:
	int counter=0;
	int frame=0;
	VideoCapture cap;
	Mat imgTmp;
	CV();
	//char redDetect();
	//char blueDetect();
	//char greenDetect();
	//char yellowDetect();
	//char colourChooser();
	char colourDetector(int,int,int,int,int,int);
	char colourPicker();
};