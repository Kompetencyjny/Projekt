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