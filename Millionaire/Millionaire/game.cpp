#include "game.h"
#include "manual_functions.h"
#include "rules.h"
#include "hpfunctions.h"
#include "questions.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string categGame;				// category of current game
int level = 1;				    // level of current game
vector<string> qIdsForLevel;    // questions for current level
QuestionsList qList;
string player;

int money[] = { 500, 1500, 3000, 5000, 10000, 15000, 25000, 50000, 70000, 100000 };

void Begin()
{
	cout << "\n\n\t\t\tWELCOME TO 'WHO WANTS TO BE A MILLIONAIRE' - THE QUIZ GAME!\n\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
		<< "\tHow would you like to be adressed as? (Enter a name): ";
	cin.ignore();
	getline(cin, player);
	cout << "\n\n\t\t\tChoose a category to play in: \n\n";

	vector<string> categories = GetCategories();
	int i = 0;
	for (; i < categories.size(); i++)
	{
		cout << "\t\t" << i+1 << ". " << categories[i] << endl;
	}
	cout << "\n\t\t" << i + 1 << ". All categories"  << endl;

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
		<< "\tPlayer: " << player << "          Level: " << level << "              Category : "<< categGame << "            Question for $" << money[level - 1] << "\n"
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

int FindIndexOfRightAnswer(Question& q)
{
	for (int i = 0; i < 4; i++)
	{
		if (q.answers[i] == q.rigthAnswer)
		{
			return i;
		}
	}
}

void Lifeline50(Question& q)
{
	int indexOfRightAnswer = FindIndexOfRightAnswer(q);
	srand((unsigned)time(NULL));
	string empty = "";
	int randomN = (rand() % 4);
	if (randomN == indexOfRightAnswer)
	{
		if (randomN == 0)
		{
			q.answers[3] = empty;
		}
		else
		{
			q.answers[randomN - 1] = empty;
		}
	}
	else
	{
		q.answers[randomN] = empty;
	}

	randomN = (rand() % 4);
	if (randomN == indexOfRightAnswer)
	{
		if (randomN == 0)
		{
			if (q.answers[3] != empty)
			{
				q.answers[3] = empty;
			}
			else
			{
				q.answers[1] = empty;
			}
			
		}
		else
		{
			if (q.answers[randomN - 1] != empty)
			{
				q.answers[randomN - 1] = empty;
			}
			else if (randomN == 3)
			{
				q.answers[0] = empty;
			}
			else
			{
				q.answers[randomN + 1] = empty;
			}
		}
	}
	else if (q.answers[randomN] == empty)
	{
		if (randomN == 0)
		{
			if (indexOfRightAnswer != 3)
			{
				q.answers[3] = empty;
			}
			else
			{
				q.answers[1] = empty;
			}
		}
		else
		{
			if (randomN - 1 != indexOfRightAnswer)
			{
				q.answers[randomN - 1] = empty;
			}
			else if (randomN == 3)
			{
				q.answers[0] = empty;
			}
			else
			{
				q.answers[randomN + 1] = empty;
			}
		}
	}
	else
	{
		q.answers[randomN] = empty;
	}
}

void LifelineCallAFriend(Question& q)
{
	int index = IndexOfAnswerForLifeline(q);
	string letter;
	switch (index)
	{
	case 0:
		letter = 'A';
		break;
	case 1:
		letter = 'B';
		break;
	case 2:
		letter = 'C';
		break;
	case 3:
		letter = 'D';
		break;
	}
	string answer = letter + ") " + q.answers[index] + ".";
	vector<string> calls =
	{
		"Hello" + player + ", I think the right answer is " + answer ,
		"Hey, Big " + player.substr(0, 1) + ", the right answer is " + answer ,
		"Hii, darling, I am so honoured to be your choice to call! In my opinion, the right answer is " +  answer,
		"The answer you are looking for is " + answer,
		"Hmmm, I'm not really sure, but I think it is " + answer,
		"This is not really my strong side, but I am pretty sure it's " + answer,
		"The right answer is " + answer + ".",
		"Oh, " + player + "but that's so easy! It's " + answer
	};
}

void LifelineAskAudience(Question& q)
{
	
}

// for 'Call a friend' and 'Ask Audience' lifelines
int IndexOfAnswerForLifeline(Question& q)
{
	int level = ConvertStringToInt(q.level);
	int indexOfRightAnswer = FindIndexOfRightAnswer(q);

	srand((unsigned)time(NULL));

	// empty answers could be received if before calling this lifeline
	// the lifeline 50/50 was called for the same question 
	// the empty answers are either 0 or 2
	bool emptyAnswers = false;
	for (int i = 0; i < 4; i++)
	{
		if (q.answers[i] == "")
		{
			emptyAnswers = true;
			break;
		}
	}

	// depending on the level of difficulty, there is different percent chance for a wrong answer
	// easy (level 1 - 3) - 30%
	// medium (level 4 - 6) - 60%
	// hard (level 7 - 10) - 80%
	// so to make the random selection, we will use the digits from 0 to 9
	int randomN = (rand() % 9);

	// whatever number we get from calling the rand() function, this is how we would know if it's the right answer
	// easy - 0 1 2 3 4 5 6 | 7 8 9 (if the random chosen digit is from 0 to 6, we've goten the right answer)
	// medium - 0 1 2 3 | 4 5 6 7 8 9 (we've gotten the right answer if the random digit is from 0 to 3)
	// medium - 0 1 | 2 3 4 5 6 7 8 9 (we've gotten the right answer if the random digit is either 0 or 1)

	// if we don't get the right answer though, then a random answer from the wrong ones is returned
	int indexOfWrongAnswer = (rand() % 4);

	if (indexOfWrongAnswer == indexOfRightAnswer)
	{
		if (!emptyAnswers)
		{
			if (randomN == 0)
			{
				indexOfWrongAnswer = 3;
			}
			else
			{
				indexOfWrongAnswer -= 1;
			}
		}
	}

	if ((level >= 1 && level <= 3 && randomN <= 6) ||
		(level >= 4 && level <= 6 && randomN <= 3) ||
		(level >= 7 && level <= 10 && randomN <= 1))
	{
		return indexOfRightAnswer;
	}
	else
	{
		return indexOfWrongAnswer;
	}
}
