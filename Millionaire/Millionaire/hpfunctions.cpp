
#include <iostream>
#include "hpfunctions.h"
#include "rules.h"
using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#else
    for (int i = 0; i <= 1000; i++)
    {
        cout << endl;
    }
#endif
}
void Play()
{
    clearScreen();
    cout << "Let's start";
}

void Rules()
{
    clearScreen();
    DisplayRules();
}

void AddQuestion()
{
    clearScreen();
}

void EditQuestion()
{
    clearScreen();
}

void InvalidInput() 
{
    cout << "\nInvalid input! Please type your choice again: ";
}