#include <iostream>
#include <iomanip>
#include <string>
#include "hpfunctions.h"
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

int main()
{
   Homepage();
}