
#include <iostream>
#include "hpfunctions.h"
#include "rules.h"
#include "questions.h"
#include <iomanip>
#include <string>
using namespace std;

void Homepage()
{
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
    case 1: 
        Play();
        break;
    case 2: 
        Rules();
        break;
    case 3: 
        AddQuestion();
        break;
    case 4: 
        clearScreen();
        EditQuestionHome();
        break;
    case 5: 
        return;
    default: 
        InvalidInput();
        Homepage();
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
    string n; 
    cin >> n;

#endif
}

void Play()
{
    clearScreen();
    cout << "Let's start";
    FillQuestions();
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
    cout << endl;
    pressAnyKeyToContinueSimulation();
    clearScreen();
    Homepage();
}

void EditQuestionHome()
{
    cout << "\n   CHOOSE QUESTION TO EDIT\n";
    
    cout << "\n  Do you want all the questions to be displayed or would you want\n"
         << "  to search for a specific question with a keyword/s to edit it?\n";
    cout << "\n  Type 'a'/'A' for all questions or 's'/'S' to search: ";
    string opt;
    cin >> opt;
    opt = returnStringToLower(opt);
    clearScreen();
    cout << "\n   EDIT QUESTION FORM\n";
    cout << "\n //'ID: question' format of display//\n";

    if (opt == "a")
    {
        cout << "\n   All questions are being displayed.\n\n";
        DisplayQuestions("");
    }
    else if (opt == "s")
    {
        cout << "\nType in a keyword/s: ";
        string keyword;
        cin.ignore();
        getline(cin, keyword);
        cout << "\n   Questions that contain the keyword in their category, body, or in their answers are being displayed.\n\n";
        DisplayQuestions(keyword);
    }
    else
    {
        InvalidInput();
        EditQuestionHome();
    }
    cout << "\n Type the ID of the question you would like to edit: ";
    
    Question qToEdit;
    string id;
    cin >> id;
   // qToEdit = ;
    while (FindQuestionById(id)==NULL)
    {
        cout << "\nInvalid ID! Please type it again: ";
        cin >> id;
       // qToEdit = FindQuestionById(id);
    }
    EditQuestion(*(FindQuestionById(id)));
}

void EditQuestion(Question qToEdit)
{ 
    clearScreen();
    cout << "\n   EDIT QUESTION FORM\n";
    cout << "\n\n   This is the question of your choice: \n\n";

    PrintWholeQ(qToEdit);
    EditQ(qToEdit);

    //PrintWholeQ(FindQuestionById(id));
    pressAnyKeyToContinueSimulation();
    clearScreen();
    Homepage();
}

void InvalidInput() 
{
    clearScreen();
    cout << "\n  Invalid input! Please try typing your choice again! \n\n";
}