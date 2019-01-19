#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "windows.h"

using namespace cv;
using namespace std;

class CV
{
public:
	//VideoCapture cap;
	int counter=0;
	char colourDetector();
	char colourPicker();
};