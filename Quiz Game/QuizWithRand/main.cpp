#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>
#include "question.hpp"

using namespace std;

int main()
{
    Question controller;
    while(controller.menuChoice != 4)
    {
        controller.showMenu();
        controller.parseChoice();
        controller.switchChoice();
        controller.checkChoice();
    }

   return 0;
}