#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "question.hpp"
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>
#include <time.h>

using namespace cv;
using namespace std;

int frame=0;
int counter = 0;

char redDetect();
char blueDetect();
char greenDetect();
char yellowDetect();
char colourChooser();

void Question::showMenu()
{
    SetConsoleTextAttribute(uchwyt, 15);//ZMIEN KOLOR NA NR 15=WHITE
    //MAIN MENU
    system("cls");
    cout<<"==============================================================================="<<endl;
    SetConsoleTextAttribute(uchwyt, 14);//ZMIEN KOLOR NA NR 14=YELLOW
    cout<<"                                 WELCOME TO QUIZY!"<<endl;
    SetConsoleTextAttribute(uchwyt, 15);//PRZYWROC KOLOR BIALY
    cout<<"==============================================================================="<<endl;
    SetConsoleTextAttribute(uchwyt, 12);
    cout<<"					"<<char(2)<<endl;
    SetConsoleTextAttribute(uchwyt, 15);
    cout<<"==============================================================================="<<endl;
    SetConsoleTextAttribute(uchwyt, 11);
    cout<<"                                    1.START"<<endl;
    cout<<"                                  2.HIGHSCORE"<<endl;
    cout<<"                                 3.HOW TO PLAY"<<endl;
    cout<<"                                     4.EXIT"<<endl;
    SetConsoleTextAttribute(uchwyt, 15);
    cout<<"==============================================================================="<<endl;
    SetConsoleTextAttribute(uchwyt, 12);
    cout<<"CHOOSE OPTION: ";
    SetConsoleTextAttribute(uchwyt, 15);
    cin>>choice;
}

void Question::howToPlay()
{
    system("cls");
    cout<<"==============================================================================="<<endl;
    cout<<"                             HOW TO PLAY INSTRUCTION"<<endl;
    cout<<"==============================================================================="<<endl;
    cout<<"                            HOW TO CHOOSE YOUR ANSWEAR:"<<endl;
    SetConsoleTextAttribute(uchwyt, 4);
    cout<<"                      IF YOU WANT CHOOSE ANSWER A SHOW RED FLAG."<<endl;
    SetConsoleTextAttribute(uchwyt, 1);
    cout<<"                      IF YOU WANT CHOOSE ANSWER B SHOW YELLOW FLAG."<<endl;
    SetConsoleTextAttribute(uchwyt, 2);
    cout<<"                      IF YOU WANT CHOOSE ANSWER C SHOW BLUE FLAG."<<endl;
    SetConsoleTextAttribute(uchwyt, 14);
    cout<<"                      IF YOU WANT CHOOSE ANSWER D SHOW GREEN FLAG."<<endl;
    cout<<"==============================================================================="<<endl;
    system("pause");
}

void Question::parseChoice()
{
    for(int i=0; i<choice.length(); i++)
    {
        if ((choice[i]<48)||(choice[i]>57))
        {
            wrongOption = true;
        }
    }
    if(wrongOption==false)
    {
        menuChoice=atoi(choice.c_str());
    }
}

void Question::switchChoice()
{
    switch(menuChoice)
    {
        case 1: showQuestion(); break;
        case 2: Highscore(); break;
        case 3: howToPlay();break;
        case 4: {
                    cout<<endl<<"END OF QUIZ!"<<endl;
                    exit(0);
                } break;
        default: wrongOption=true; break;
    }
}

void Question::checkChoice()
{
    if (wrongOption==true) //NIEPOPRAWNA OPCJA W MENU
    {
        cout<<endl;
        SetConsoleTextAttribute(uchwyt, 12);
        cout<<"==============================================================================="<<endl;
        cout<<"                       YOU DIDN'T CHOOSE CORRECT OPTION!"<<endl;
        cout<<"==============================================================================="<<endl<<endl;
        SetConsoleTextAttribute(uchwyt, 15);
        system("pause");
    }
}

void Question::read()
{
   fstream plik;
   plik.open("quiz.txt",ios::in);

   if(plik.good()==false)
   {
      cout<<"OPENING FILE FAILED!";
      exit(0);
   }

    int lineNumber=1;
    string line;
    int questionNumber=0;

    while(getline(plik,line))
    {
         switch(lineNumber)
         {
             case 1: content[questionNumber] = line;      break;
             case 2: A[questionNumber] = line;       break;
             case 3: B[questionNumber] = line;       break;
             case 4: C[questionNumber] = line;       break;
             case 5: D[questionNumber] = line;       break;
             case 6: correct[questionNumber] = line;   break;
         }
         if(lineNumber==6)
         {
             lineNumber=0;
             questionNumber++;
         }
         lineNumber++;
     }

    plik.close();
}

void Question::showQuestion()
{
    read();
    system("cls");
    cout<<"==============================================================================="<<endl;
    cout<<"                               QUIZY START"<<endl;
    cout<<"==============================================================================="<<endl;
    for (int i=0; i<=59; i++)
    {
		randomowa = rand() % 60;
		SetConsoleTextAttribute(uchwyt, 14);
        cout<<endl<<content[randomowa]<<endl;
        SetConsoleTextAttribute(uchwyt, 15);
        cout<<"==============================================================================="<<endl;
        SetConsoleTextAttribute(uchwyt, 4);
        cout<<"A. "<<A[randomowa]<<endl;
        SetConsoleTextAttribute(uchwyt, 14);
        cout<<"B. "<<B[randomowa]<<endl;
        SetConsoleTextAttribute(uchwyt, 1);
        cout<<"C. "<<C[randomowa]<<endl;
        SetConsoleTextAttribute(uchwyt, 2);
        cout<<"D. "<<D[randomowa]<<endl;
        SetConsoleTextAttribute(uchwyt, 15);
        cout<<"==============================================================================="<<endl;
        SetConsoleTextAttribute(uchwyt, 14);
        cout<<"SHOW UR ANSWER: ";
		answer = colourChooser();;

        //transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if(answerCheck == check(randomowa))
        {
            break;
        }
    }
}

bool Question::check(int i)
{
    if(answer == correct[i])
    {
        SetConsoleTextAttribute(uchwyt, 10);
        cout<<endl<<"+1 POINT!"<<endl;
        points++;
        return true;
    }
    else
    {
        SetConsoleTextAttribute(uchwyt, 12);
        cout<<endl<<"WRONG! CORRECT ANSWEAR: "<<correct[i]<<endl;
        summary();
        return false;
    }
}

void Question::summary()
{
    SetConsoleTextAttribute(uchwyt, 11);
    cout<<endl<<"END OF QUIZ!"<<endl;
    cout<<endl<<"INSERT YOUR NAME: ";
    cin>>nick;
    cout<<nick<<" YOUR SCORE -> ";
    SetConsoleTextAttribute(uchwyt, 15);
    cout<<points<<endl<<endl;
	save(nick,points);
    system("pause");
    //showMenu();
}
void Question::Highscore()
{
    system("cls");
    cout<<"==============================================================================="<<endl;
    cout<<endl<<"                                   HIGHSCORE"<<endl;
    cout<<"==============================================================================="<<endl;
    show(false);
    //cin.sync();
    //cin.get();
    system("pause");
}

void Question::show(bool _loadOnly)
{
    bool loadOnly=_loadOnly;
    int lineNum=0;
    string osoby[5];
    string line;
    string wyniki[5];
    fstream plik2;



   plik2.open("wyniki.txt",ios::in);

   if (plik2.good()==false)
        {
            cout<<"Problem with file!"<<endl<<endl;
            exit(0);
        }
        while(getline(plik2,line))
            {
                if(lineNum%2==0)
                {
                    osoby[lineNum]=line;
                    if(!loadOnly)
                    cout<<"Nickname : \t"<<line<<endl;
                }
                if(lineNum%2==1)
                {
                    wyniki[lineNum]=line;
                    if(!loadOnly)
                    cout<<"Score : \t"<<line<<endl;
                }
                lineNum++;
            }
   plik2.close();
}

void Question::save(string _name,int _points)
{
    int lineNum=0;
    string name=_name;
    int points=_points;
    string osoby[6];
    string osobyTemp[6];
    string line;
    string wyniki[6];
    string wynikiTemp[6];
    fstream plik2;
    fstream plik3;
    int position=-1;
    int pointsAsIntFromFile=0;


   plik2.open("wyniki.txt",ios::in);

   if (plik2.good()==false)
        {
            cout<<"Problem with file!"<<endl<<endl;
            exit(0);
        }
        while(getline(plik2,line))
            {
                if(lineNum%2==0)
                {
                    osoby[(lineNum)/2]=line;
                }
                if(lineNum%2==1)
                {
                    wyniki[(lineNum-1)/2]=line;
                    pointsAsIntFromFile=atoi(line.c_str());
                    if(points>pointsAsIntFromFile&&position==-1)
                    position=(lineNum-1)/2;
                }
                lineNum++;
            }

    plik2.close();

            if(position>=0)
            {
                plik3.open("wyniki.txt",ios::out);

            if (plik3.good()==false)
                {
                    cout<<"Problem with file!"<<endl<<endl;
                    exit(0);
                }

                string tmp;
                string tmp2;//int na string
                sprintf((char*)tmp.c_str(), "%d", points);
                string str = tmp.c_str();

                cout<<"Position\t :"<<position<<endl; // jaka pozycja w wynikach
                cin.sync();
                cin.get();


                for (int i=0;i<=(lineNum-1)/2;i++)//do pliku z tablicy lokalnej
                {
                    if(i==position)
                    {
                    plik3<<name<<endl<<str<<endl;
                    }
                    if(i>position)
                    {
                    plik3<<osoby[i-1]<<endl<<wyniki[i-1]<<endl;
                    }
                    if(i<position)
                    {
                    plik3<<osoby[i]<<endl<<wyniki[i]<<endl;
                    }
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
			//cout << "RED DONE!!!!!!!!!!!!!";
			return 'a';
		}
		if (yellowDetect() == 'b') {
			//cout << "Yellow DONE!!!!!!!!!!!!!";
			return 'b';
		}
		if (blueDetect() == 'c') {
			//cout << "Blue DONE!!!!!!!!!!!!!";
			return 'c';
		}
		if (greenDetect() == 'd') {
			//cout << "Green DONE!!!!!!!!!!!!!";
			return 'd';
		}
	}
	//return 'e';
}


char redDetect()
{
	VideoCapture cap(0); //capture the video from webcam
	int iLowH = 0;
	int iHighH = 11;
	int iLowS = 112;
	int iHighS = 255;
	int iLowV = 108;
	int iHighV = 255;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream RED" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																									  //morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			//cout << "Red block on the screen" << endl;
			destroyAllWindows();
			cap.release();
			return 'a';

		}


		//cout << frame;
		frame++;
		if (frame == 5)
		{
			frame = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}



char blueDetect()
{
	VideoCapture cap(0); //capture the video from webcam
	int iLowH = 65;
	int iHighH = 115;
	int iLowS = 63;
	int iHighS = 255;
	int iLowV = 60;
	int iHighV = 255;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream Blue" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																									  //morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			//cout << "Blue block on the screen" << endl;
			cap.release();
			destroyAllWindows();
			return 'c';
		}


		//cout << frame;
		frame++;
		if (frame == 5)
		{
			frame = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}



char greenDetect()
{
	VideoCapture cap(0); //capture the video from webcam
	int iLowH = 36;
	int iHighH = 55;
	int iLowS = 45;
	int iHighS = 255;
	int iLowV = 60;
	int iHighV = 255;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream GREEN" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																									  //morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			//cout << "Green block on the screen" << endl;
			cap.release();
			destroyAllWindows();
			return 'd';
		}


		//cout << frame;
		frame++;
		if (frame == 5)
		{
			frame = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}



char yellowDetect()
{
	VideoCapture cap(0); //capture the video from webcam
	int iLowH = 15;
	int iHighH = 36;
	int iLowS = 130;
	int iHighS = 255;
	int iLowV = 105;
	int iHighV = 255;

	//Capture a temporary image from the camera
	Mat imgTmp;
	cap.read(imgTmp);

	//Create a black image with the size as the camera output
	Mat imgLines = Mat::zeros(imgTmp.size(), CV_8UC3);;

	while (true)
	{
		Mat imgOriginal;

		bool bSuccess = cap.read(imgOriginal); // read a new frame from video



		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream YELLOW" << endl;
			break;
		}

		Mat imgHSV;

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		Mat imgThresholded;

		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

																									  //morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (removes small holes from the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		counter = countNonZero(imgThresholded);

		if (counter > 35000)
		{
			//cout << "Yellow block on the screen" << endl;
			cap.release();
			destroyAllWindows();
			return 'b';
		}

		//cout << frame;
		frame++;
		if (frame == 5)
		{
			frame = 0;
			destroyAllWindows();
			cap.release();
			return 'e';
		}
	}
}
