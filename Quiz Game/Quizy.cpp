#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;


const double DIFF_LEVEL_ONE = 1.23;
const double DIFF_LEVEL_TWO = 1.51;
const double DIFF_LEVEL_THREE = 2.02;

int main()
{


    ///Declare the necessary variables, for example:
    ofstream outFile;           
    ifstream inFile;
    string alias;               
    string date;              
    string A, B, C, D;
    string question;
    int questions;      
    int difficulty;      
    int counter;
    int correct;
    double multiplier;
    char theAnswer;
    char Answer;
    char answer;

    
    ///prompt for the user information (Game alias and date).
    cout << "Enter the name for the game: ";
    cin >> alias;
    cout << "Enter the date (example: Oct/12/2017): ";
    cin >> date;

    ///step3 (done):
    ///use user's Game Name to create a new output file.
    alias = alias.append(".txt");
    outFile.open(alias.c_str(), ios::app);

    do {
    cout << "How many questions? <1 - 15>: ";
    cin >> questions;
    if (1> questions || questions > 15)
    {
       cout << "You entered an invalid answer." << endl;
    }
    else
        break;
    }
    while (1 <= questions || questions >= 15);

    ///step5
    ///ask the user to enter the difficulty level.
    /// check the difficulty level.
    /// If the difficulty level is not within the acceptable range, display the error message and exit the program.
    cout << "Enter difficulty level: <1,2,3>: ";
    cin >> difficulty;
    if (1> difficulty || difficulty > 3)
    {
        cout << "Invalid difficulty level! Try again later. " << endl << endl;
    }
    ///step6
    /// open the correct input file
    /// use the files(questions1.txt or questions2.txt or questions3.txt) based on the level.
    switch (difficulty)
    {
    case 1:
        inFile.open("questions1.txt");
            multiplier = DIFF_LEVEL_ONE;
            break;
    case 2:
        inFile.open("questions2.txt");
            multiplier = DIFF_LEVEL_TWO;
            break;
    case 3:
        inFile.open("questions3.txt");
            multiplier = DIFF_LEVEL_THREE;
            break;
    default:
        return 1;
    }

    ///step7
    ///you will need to START a LOOP here to repeat steps 7.1, 7.2, 7.3, 7.4, 7.5, and 7.6 for all questions:
    ///for example, if the user entered the number of questions = 5, then the loop will run 5 times.
                    ///step 7.1
                    ///read the question, the correct answer, and the 4 options from the input file.
    for (counter=1; counter<=questions; counter++){
        getline(inFile, question);
        inFile >> theAnswer;
        inFile >> A;
        inFile >> B;
        inFile >> C;
        inFile >> D;

                    ///step 7.2
                    ///Print the question along with the options on screen.
                    ///step 7.3
                    ///Ask the user for his choice.
    cout << question << endl;
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;
    cout << "C: " << C << endl;
    cout << "D: " << D << endl;
    cin >> Answer;

                    ///step 7.4
                    ///Convert the user choice into upper case letter. Use toupper() to convert a char to uppercase.
    answer = toupper(Answer);

                    ///step 7.5
                    ///If the user choice matches the solution, Then print it as correct and calculate the score.
        if (answer != 'A' && answer != 'B' && answer != 'C' && answer != 'D')
        {
            cout << "You entered an invalid answer! Try again later. " << endl;
            cin >> Answer;
        }
        if (answer == theAnswer)
        {
            cout << "CORRECT! " << endl;
            correct++;
        }
                   
        else
            cout << "Wrong answer! Better luck next time. " << endl;
            cout << theAnswer << endl;
}
   
    cout << "______________________________\n";
    cout << "GameName: " << alias << endl;
    cout << "Score: " << correct * multiplier << endl;
    cout << "______________________________\n";

  
    outFile << date <<  difficulty <<  correct * multiplier << endl;

   
    outFile.close();
    inFile.close();
    return 0;
}