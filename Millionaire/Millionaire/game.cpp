#include "game.h"
#include "rules.h"
#include "hpfunctions.h"
#include "questions.h"
#include <iostream>
#include <vector>
using namespace std;

string categoryOfCurrentGame;

int ConvertStringToInt(string str)
{
	int number = 0; 
	int multBy10 = 1;
	for (int i = str.size()-1; i >= 0; i--)
	{
		if (str[i] <= 48 || str[i] > 57)
		{
			return -1;
		}
		number += (str[i] - 48) * multBy10;
		multBy10 *= 10;
	}
	return number;
}

void Begin()
{
	cout << "\n\n\t\t\tWELCOME TO 'WHO WANTS TO BE A MILLIONAIRE' - THE QUIZ GAME!\n\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
		
		<< "\t\t\tChoose a category to play in: \n\n";

	vector<string> categories = GetCategories();
	int i = 0;
	for (; i < categories.size(); i++)
	{
		cout << "\t\t" << i+1 << ". " << categories[i] << endl;
	}
	cout << "\t\t" << i + 1 << ". All categories"  << endl;

	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\tNOTICE: If the category of your choice does not have enough questions to run for the game, then a random\n"
		<< "\tquestion from the rest of the categories would be chosen at the same difficulty level. \n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	cout << "\n\tType the number of your chosen category (to go back, type 'M'): ";
	string input;
	cin >> input;

	if (input=="M")
	{
		clearScreen();
		Homepage();
	}

	int categoryNum = ConvertStringToInt(input);
	while(categoryNum ==-1 || categoryNum >categories.size()+1)
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
		categoryNum = ConvertStringToInt(input);
	}

	if (categoryNum==i+1)
	{
		categoryOfCurrentGame = "All";
	}
	else
	{
		categoryOfCurrentGame = categories[categoryNum-1];
	}
	
	clearScreen();
	RulesShort();
	pressAnyKeyToContinueSimulation();
}