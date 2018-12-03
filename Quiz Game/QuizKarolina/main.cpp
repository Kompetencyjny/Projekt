#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <windows.h>


using namespace std;

int menuChoice = 0;
string choice;
bool wrongOption = false;
HANDLE uchwyt = GetStdHandle(STD_OUTPUT_HANDLE); // pozwoli zmieniac kolor czcionki w konsoli

void howToPlay();
void show(bool _loadOnly);
void save(string _name,int _points);

int main()
{
    while(menuChoice != 4)
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

        string nick;
        string content[5], A[5], B[5], C[5], D[5], correct[5];
        string answer;
        int points=0;

        //ZMIENNE POMOCNICZE
        int lineNumber=1;
        string line;
        int questionNumber=0;
        fstream plik;
        fstream plik2;

        switch(menuChoice)
        {
            case 1: plik.open("quiz.txt",ios::in); break;
            case 2: {
                     cout<<endl<<"Highscore"<<endl;
                     show(false);
                     cin.sync();
                     cin.get();
                     plik.open("quiz.txt",ios::in);
                    } break;
            case 3: {
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
                        exit (0);
                    } break;
            case 4: {
                        cout<<endl<<"Wypierdalaj!"<<endl;
                        exit(0);
                    } break;
            default: wrongOption=true;
        }

        if (plik.good()==false)
        {
            cout<<"Z³y plik!"<<endl<<endl;
        }
        else if (wrongOption==true) //NIEPOPRAWNA OPCJA W MENU
        {
            cout<<endl;
            SetConsoleTextAttribute(uchwyt, 12);
            cout<<"==============================================================================="<<endl;
            cout<<"                         Nie ma takiej opcji w menu!"<<endl;
            cout<<"==============================================================================="<<endl<<endl;
            SetConsoleTextAttribute(uchwyt, 15);
            system("pause");
        }
        else //POBIERZ LINIE Z PLIKU TXT DO ODPOWIEDNICH ZMIENNYCH
        {
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
                if (lineNumber==6)
                {
                    lineNumber=0;
                    questionNumber++;
                }
                lineNumber++;
            }

            //ZAMKNIECIE PLIKU
            plik.close();

            //PRZEPROWADZENIE TESTU
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

                if (answer==correct[i])
                {
                    SetConsoleTextAttribute(uchwyt, 10);
                    cout<<endl<<"+1 PKT!"<<endl;
                    points++;
                }
                else
                {
                    SetConsoleTextAttribute(uchwyt, 12);
                    cout<<endl<<"Blad! Poprawna odpowiedz: "<<correct[i]<<endl;
                    break;
                }
                SetConsoleTextAttribute(uchwyt, 15);
            }
            //PODSUMOWANIE WYNIKOW
            SetConsoleTextAttribute(uchwyt, 11);
            cout<<endl<<"Koniec Quizu!"<<endl;
            cout<<endl<<"Podaj swoj nick: ";
            cin>>nick;
            cout<<nick<<" liczby twoich punktow -> ";
            SetConsoleTextAttribute(uchwyt, 15);
            cout<<points<<"/5"<<endl<<endl;

            save(nick,points);

            if (points==5)
            {
                SetConsoleTextAttribute(uchwyt, 12);
                cout<<"FLAWLESS VICTORY!"<<endl<<endl;
                SetConsoleTextAttribute(uchwyt, 15);
            }
            system("pause");
        }

    }
    return 0;
}

void howToPlay()
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
}
void show(bool _loadOnly)
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
            cout<<"Problem z plikiem!"<<endl<<endl;
            exit(0);
        }
        while(getline(plik2,line))
            {
                if(lineNum%2==0)
                {
                    osoby[lineNum]=line;
                    if(!loadOnly)
                    cout<<"Osoba : \t"<<line<<endl;
                }
                if(lineNum%2==1)
                {
                    wyniki[lineNum]=line;
                    if(!loadOnly)
                    cout<<"Wynik : \t"<<line<<endl;
                }
                lineNum++;
            }
   plik2.close();
}

void save(string _name,int _points)
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
            cout<<"Problem z plikiem!"<<endl<<endl;
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
                    cout<<"Problem z plikiem!"<<endl<<endl;
                    exit(0);
                }

                string tmp;
                string tmp2;//int na string
                sprintf((char*)tmp.c_str(), "%d", points);
                string str = tmp.c_str();

                cout<<"Pozycja\t :"<<position<<endl; // jaka pozycja w wynikach
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
