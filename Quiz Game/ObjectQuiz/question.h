#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

class Question
{
   public:

    string content[5];
    string A[5],B[5],C[5],D[5];
    int questionNumber;
    string correct[5];
    char answer;
    int points = 0;
    string nick;
    int menuChoice = 0;
    string choice;
    bool wrongOption = false;
    bool answerCheck = false;
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
