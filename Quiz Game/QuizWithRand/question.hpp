#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>
#include <time.h>
#include <iostream>
#include "windows.h" 

#define QuizSize 60

using namespace std;
class Question
{
   public:

    string content[QuizSize];
    string A[QuizSize],B[QuizSize],C[QuizSize],D[QuizSize];
    int questionNumber;
    string correct[QuizSize];
    string answer;
    int points = 0;
    string nick;
    int menuChoice = 0;
    string choice;
    bool wrongOption = false;
    bool answerCheck = false;
	int randomowa;
    HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE);

    void read(); //wczytuje pytania z pliku
    void showQuestion(); //pokazuje pytanie, czyta odpowiedz
    bool check(int i); //sprawdza poprawnosc odpowiedzi
    void startGame();
    void summary();
    void showMenu();
    void howToPlay();
    void parseChoice();
    void switchChoice();
    void checkChoice();
    void show(bool _loadOnly);
    void save(string _name,int _points);
    void Highscore();

};