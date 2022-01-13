#include "game.h"
#include "manual_functions.h"
#include "rules.h"
#include "hpfunctions.h"
#include "questions.h"
#include <iostream>
#include <vector>
using namespace std;

string categGame; // categogy of current game
//vector<Question> questions; // questions for current game



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
		GoBackToMain();
	}

	int categoryNum = ConvertStringToInt(input);
	while(categoryNum <= 0 || categoryNum >categories.size()+1 )
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
		if (input == "M")
		{
			GoBackToMain();
		}
		categoryNum = ConvertStringToInt(input);
	}

	if (categoryNum==i+1)
	{
		categGame = "All";
	}
	else
	{
		categGame = categories[categoryNum-1];
	}
	
	clearScreen();
	RulesShort();
	pressAnyKeyToContinueSimulation();
}

void NewGame()
{

}

void GetQuestionsForCurrentGame()
{
	//questions.clear();
	//int qPerLevel[10] = { 0,0,0,0,0,0,0,0,0,0 }; // in this array we will see how many questions available are there per level
	//
	//
	//if (categGame == "All" )
	//{
	//	questions = Questions();
	//}

	//Question q;

	//// with this loop we get all the questions with the chosen category for the game
	//for (int i = 0; i < questions.size(); i++)
	//{
	//	q = Questions()[i];
	//	if (q.category == categGame)
	//	{
	//		questions.emplace_back(q);
	//		qPerLevel[ConvertStringToInt(q.level) - 1] += 1;
	//	}
	//}

	// with this loop we check if there are levels with zero questions 
	// (which means there aren't questions from this category for that level)
	// and if there is one (or more) found, then we get the rest of the 
	// questions for the same level but from different category
	/*for (int i = 0; i < 10; i++)
	{
		if (qPerLevel[i] == 0)
		{
			for (int j = 0; j < allQ.size(); j++)
			{
			    q = allQ[j];
				if (ConvertStringToInt(q.level) - 1 == i)
				{
					questions.emplace_back(q);
					qPerLevel[i] += 1;
				}
			}
		}
	}*/

}