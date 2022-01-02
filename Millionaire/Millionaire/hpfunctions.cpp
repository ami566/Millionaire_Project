
#include <iostream>
#include "hpfunctions.h"
#include "rules.h"
#include "questions.h"
#include <iomanip>
using namespace std;

void Homepage()
{
    clearScreen();
    int option;
    cout << "\n\n\n" << setw(70) << "WHO WANTS TO BE A MILLIONAIRE\n" << setfill('*')
        << setw(150) << "\n\t  A quiz game presented to you by Amira Emin\n";
    // cout.setf(ios::internal);
    cout.width(100);
    cout << "\n\n\t\t1. New Game";
    cout << "\n\n\t\t2. Game Rules";
    cout << "\n\n\t\t3. Add new question";
    cout << "\n\n\t\t4. Edit an existing question";
    cout << "\n\n\t\t5. Exit";
    cout << "\n\nEnter your choice (1 - 5): ";
    cin >> option;

    switch (option)
    {
    case 1: Play();
        break;
    case 2: Rules();
        break;
    case 3: AddQuestion();
        break;
    case 4: EditQuestion();
        break;
    case 5: return;
    default: InvalidInput(); // have to edit
        break;
    }
}

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

void pressAnyKeyToContinueSimulation()
{
#ifdef _WIN32
    system("pause");
#elif __linux__
    system("read");
#else
    cout << "Press any key and then the 'Enter' key to continue . . .";
    string n; cin >> n;

#endif
}

void Play()
{
    clearScreen();
    cout << "Let's start";
    GetQuestions();
}

void Rules()
{
    clearScreen();
    DisplayRules();

    pressAnyKeyToContinueSimulation();
    Homepage();
}

void AddQuestion()
{
    clearScreen();
    cout << "\n   ADD NEW QUESTION FORM\n";
    AddQuestionToFile(GetQuestionFromInput());
    pressAnyKeyToContinueSimulation();
    Homepage();
}

void EditQuestion()
{
    clearScreen();
}

void InvalidInput() 
{
    cout << "\nInvalid input! Please type your choice again: ";
}