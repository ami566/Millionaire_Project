#include "game.h"
#include "manual_functions.h"
#include "rules.h"
#include "hpfunctions.h"
#include "questions.h"
#include <iostream>
#include <vector>
using namespace std;

string categGame;				// category of current game
int level = 8;				    // level of current game
vector<string> qIdsForLevel;    // questions for current level
QuestionsList qList;

int money[] = { 500, 1500, 3000, 5000, 10000, 15000, 25000, 50000, 70000, 100000 };

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
	cout << "/n\t\t" << i + 1 << ". All categories"  << endl;

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
	clearScreen();
	GetQuestionsForCurrentGame();
	NewGame();
}

void NewGame()
{
	Question q = GetQuestionForLevel();
	Heading();
	MainPart(q);
}

void GetQuestionsForCurrentGame()
{
	qList = QuestionsForGame(categGame);
}

Question GetQuestionForLevel()
{
	int qCount = qList.qPerLevel[level - 1];
	QuestionsForLevel();
	/*if (qCount == 1)
	{
		return *FindQuestionById(qIdsForLevel[0]);
	}*/

	// generating random number within the range of the count of the available questions
	srand((unsigned)time(NULL));
	int randomQ =  (rand() % qCount);
	string qId = qIdsForLevel[randomQ];
	return *FindQuestionById(qId);
}

void QuestionsForLevel()
{
	qIdsForLevel.clear();
	for (auto& q : qList.list)
	{
		if (ConvertStringToInt(q.level) == level)
		{
			qIdsForLevel.emplace_back(q.id);
		}
	}
}

void Heading()
{
	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\tLevel: " << level << "                         Category: "<< categGame << "                         Question for $" << money[level - 1] << "\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
}

void MainPart(Question& q)
{
	cout << "\t "<< level << ". " << q.body << endl;
	ShuffleAnswers(q);
	string A = q.answers[0];
	string B = q.answers[1];
	string C = q.answers[2];
	string D = q.answers[3];
	cout << "\tA) " << A << "                 B) " << B << endl
		<< "\tC) " << C << "                 D) " << D << endl;
	
}

void ShuffleAnswers(Question& q)
{
	srand((unsigned)time(NULL));
	int randomN = (rand() % 4);
	SwapStrings(q.answers[3], q.answers[randomN]);
	randomN = (rand() % 3);
	SwapStrings(q.answers[2], q.answers[randomN]);
	randomN = (rand() % 2);
	SwapStrings(q.answers[1], q.answers[randomN]);

}