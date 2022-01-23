
#include <iostream>
#include "hpfunctions.h"
#include "manual_functions.h"
#include "rules.h"
#include "questions.h"
#include "game.h"
#include <string>
using namespace std;

void Homepage()
{
    vector<Question> questions = GetQuestions();
    int option;
    cout << "\n\n\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
        << "\t\t\t\t\tWHO WANTS TO BE A MILLIONAIRE\n" 
        << "\n\t\t\t\tA quiz game presented to you by Amira Emin\n"
        "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
    cout << "\n\n\t\t1. New Game";
    cout << "\n\t\t2. Game Rules";
    cout << "\n\t\t3. Add new question";
    cout << "\n\t\t4. Edit an existing question";
    cout << "\n\t\t5. Exit";
    cout << "\n\n\t\tEnter your choice (1 - 5): ";
    cin >> option;

    switch (option)
    {
    case 1: 
        Play(questions);
        break;
    case 2: 
        Rules();
        break;
    case 3: 
        AddQuestion(questions);
        break;
    case 4: 
        clearScreen();
        EditQuestionHome(questions);
        break;
    case 5: 
        return;
    default: 
        InvalidInput();
        Homepage();
        break;
    }
}

void Play(vector<Question>& questions)
{
    clearScreen();
    Begin(questions);
}

void Rules()
{
    clearScreen();
    DisplayRules();

    pressAnyKeyToContinueSimulation();
    GoBackToMain();
}

void AddQuestion(vector<Question>& questions)
{
    clearScreen();
    cout << "\n\t\t   ADD NEW QUESTION FORM\n";
    AddQuestionToFile(GetQuestionFromInput(questions));
    cout << endl;
    pressAnyKeyToContinueSimulation();
    GoBackToMain();
}

void EditQuestionHome(vector<Question>& questions)
{
    cout << "\n\t\t\t   CHOOSE QUESTION TO EDIT\n";
    
    cout << "\n\tDo you want all the questions to be displayed or would you want\n"
         << "\tto search for a specific question with a keyword/s to edit it?\n";
    cout << "\n\tType 'a'/'A' for all questions or 's'/'S' to search (type '0' to go back): ";
    string opt;
    cin >> opt;
    opt = returnStringToLower(opt);
    while (opt != "a" && opt != "s" && opt != "0")
    {
        cout << "\t\aInvalid input! Please type your choice again: ";
        cin >> opt;
    }

    clearScreen();
    cout << "\n\t\t\tEDIT QUESTION FORM\n";
    cout << "\n\t\t //'ID: question' format of display//\n";
    
    int qCount;

    if (opt == "a")
    {
        cout << "\n   All questions are being displayed.\n\n";
        qCount = DisplayQuestions(questions, "");
        cout << "\n\n   Total: " + to_string(qCount) + " questions \n\n";
    }
    else if (opt == "s")
    {
        cout << "\n\tType in a keyword/s: ";
        string keyword;
        cin.ignore();
        getline(cin, keyword);
        cout << "\n   Questions that contain the keyword in their category, body, or in their answers are being displayed.\n\n";
        qCount = DisplayQuestions(questions, keyword);
        if (qCount == 0)
        {
            cout << "\n   Sorry there aren't any questions that match ' " + keyword + "'.\n\n\t";
            pressAnyKeyToContinueSimulation();
            clearScreen();
            EditQuestionHome(questions);
        }
        cout << "\n\n   Total matches: " + to_string(qCount) + " questions \n\n";
    }
    else if (opt == "0")
    {
        GoBackToMain();
    }
    else
    {
        InvalidInput();
        EditQuestionHome(questions);
    }
    cout << "\n  Type the ID of the question you would like to edit (M - to go back): ";
    
    string id;
    cin >> id;
    while (FindQuestionById(questions, id)==NULL)
    {
        if (id == "M")
        {
            GoBackToMain();
        }
        cout << "  \aInvalid ID! Please type it again: ";
        cin >> id;
    }
    EditQuestion(questions, *(FindQuestionById(questions, id)));
}

void EditQuestion(vector<Question>& questions, Question q)
{ 
    clearScreen();
    cout << "\n\t\t\t\t\t\t   EDIT QUESTION FORM\n"
        << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "\n\t\t\t\t\t   This is the question of your choice: \n";
    PrintWholeQ(q);
    cout<< "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    cout << "\n\tDo you want to delete or edit the question? \n"
        << "\tType 'd' or 'D' for 'delete' and 'e', 'E' for 'edit' or '0' to go back to homepage: ";
    char input;
    cin >> input;
    // to validate the input
    while (input != 'D'&& input != 'd' && input != 'e' && input != 'E' && input != '0')
    {
        cout << "\t\aInvalid input! Please type your choice again: ";
        cin >> input;
    }

    switch (input)
    {
    case 'D':
    case 'd':
        cout << "\n\tAre you sure you want to delete this question?\n "
            << "\tType 'y' for 'yes' and 'n' for 'no': ";
        cin >> input;
        while (input != 'y' && input != 'n')
        {
            cout << "\t\aInvalid input! Please type your choice again: ";
            cin >> input;
        }
        
        if (input == 'y')
        {
            DeleteQuestion(questions, q, 'j'); // we want to delete the question from the file so we give a random value different from white space for the second parameter
            clearScreen();
            cout << "\n\n\tThe question was succesfully deleted!\n\n";
        }
        else   
            EditQuestion(questions, q);
        break;
    case 'E':
    case 'e':
        EditQ(questions, q);
        break;
    case '0':
        GoBackToMain();
    }
    pressAnyKeyToContinueSimulation();
    GoBackToMain();
}

void InvalidInput() 
{
    clearScreen();
    cout << "\n\a  Invalid input! Please try typing your choice again! \n\n";
}

