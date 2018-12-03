#include <iostream>
#include "question.h"
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>

using namespace std;

void Question::showMenu()
{
    SetConsoleTextAttribute(uchwyt, 15);//ZMIEN KOLOR NA NR 15=WHITE
    //MAIN MENU
    system("cls");
    cout<<"==============================================================================="<<endl;
    SetConsoleTextAttribute(uchwyt, 14);//ZMIEN KOLOR NA NR 14=YELLOW
    cout<<"                                   WORLD QUIZ"<<endl;
    SetConsoleTextAttribute(uchwyt, 15);//PRZYWROC KOLOR BIALY
    cout<<"==============================================================================="<<endl;
    SetConsoleTextAttribute(uchwyt, 12);
    cout<<"                              CHOOSE YOUR DESTINY "<<char(2)<<endl;
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
    cout<<"Wybierz opcje: ";
    SetConsoleTextAttribute(uchwyt, 15);
    cin>>choice;
}

void Question::howToPlay()
{
    system("cls");
    cout<<"==============================================================================="<<endl;
    cout<<"                             HOW TO PLAY INSTRUCTION"<<endl;
    cout<<"==============================================================================="<<endl;
    cout<<"                 JESLI CHCESZ WYBRAC KTORAS Z ODPOWIEDZI TO:"<<endl;
    SetConsoleTextAttribute(uchwyt, 4);
    cout<<"                PODNIES CZERWONA FLAGE ABY WYBRAC ODPOWIEDZ A."<<endl;
    SetConsoleTextAttribute(uchwyt, 1);
    cout<<"                PODNIES NIEBIESKA FLAGE ABY WYBRAC ODPOWIEDZ B."<<endl;
    SetConsoleTextAttribute(uchwyt, 2);
    cout<<"                 PODNIES ZIELONA FLAGE ABY WYBRAC ODPOWIEDZ C."<<endl;
    SetConsoleTextAttribute(uchwyt, 14);
    cout<<"                    PODNIES ZOLTA ABY WYBRAC ODPOWIEDZ D."<<endl;
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
        case 2: {
                    cout<<endl<<"Highscore"<<endl;
                    system("pause");
                } break;
        case 3: {
                    howToPlay();
                } break;
        case 4: {
                    cout<<endl<<"Koniec Quizu!"<<endl;
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
        cout<<"                         Nie ma takiej opcji w menu!"<<endl;
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
      cout<<"Nie udalo sie otworzyc pliku!";
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
    cout<<"                               WORLD QUIZ START"<<endl;
    cout<<"==============================================================================="<<endl;
    for (int i=0; i<=4; i++)
    {
        SetConsoleTextAttribute(uchwyt, 14);
        cout<<endl<<content[i]<<endl;
        SetConsoleTextAttribute(uchwyt, 15);
        cout<<"==============================================================================="<<endl;
        cout<<"A. "<<A[i]<<endl;
        cout<<"B. "<<B[i]<<endl;
        cout<<"C. "<<C[i]<<endl;
        cout<<"D. "<<D[i]<<endl;
        cout<<"==============================================================================="<<endl;
        SetConsoleTextAttribute(uchwyt, 14);
        cout<<"Twoja odpowiedz (a,b,c,d): ";
        cin>>answer;

        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if(answerCheck == check(i))
        {
            break;
        }
    }
}

bool Question::check(int i)
{
    if(answer==correct[i])
    {
        SetConsoleTextAttribute(uchwyt, 10);
        cout<<endl<<"+1 PKT!"<<endl;
        points++;
        return true;
    }
    else
    {
        SetConsoleTextAttribute(uchwyt, 12);
        cout<<endl<<"Blad! Poprawna odpowiedz: "<<correct[i]<<endl;
        summary();
        return false;
    }
}

void Question::summary()
{
    SetConsoleTextAttribute(uchwyt, 11);
    cout<<endl<<"Koniec Quizu!"<<endl;
    cout<<endl<<"Podaj swoj nick: ";
    cin>>nick;
    cout<<nick<<" liczby twoich punktow -> ";
    SetConsoleTextAttribute(uchwyt, 15);
    cout<<points<<endl<<endl;
    system("pause");
    showMenu();
}
