#include "game.h"
#include "manual_functions.h"
#include "rules.h"
#include "hpfunctions.h"
#include "questions.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Begin()
{
	Game game;
	cout << "\n\n\t\t\tWELCOME TO 'WHO WANTS TO BE A MILLIONAIRE' - THE QUIZ GAME!\n\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
		<< "\tHow would you like to be adressed as? (Enter a name): ";
	cin.ignore();
	getline(cin, game.player);
	cout << "\n\n\t\t\tChoose a category to play in: \n\n";

	vector<string> categories = GetCategories();
	int i = 0;
	for (; i < categories.size(); i++)
	{
		cout << "\t\t" << i + 1 << ". " << categories[i] << endl;
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
	while(categoryNum <= 0 || categoryNum > categories.size()+1 )
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
		if (input == "M")
		{
			GoBackToMain();
		}
		categoryNum = ConvertStringToInt(input);
	}

	if (categoryNum == i + 1)
	{
		game.category = "All";
	}
	else
	{
		game.category = categories[categoryNum-1];
	}

	/*game.level = 1;
	game.life50 = true;
	game.lifeFriend = true;
	game.lifeAudience = true;*/
	
	clearScreen();
	RulesShort();
	pressAnyKeyToContinueSimulation();
	clearScreen();
	GetQuestionsForCurrentGame(game);
	NewGame(game);
}

void NewGame(Game& g)
{
	g.question = GetQuestionForLevel(g);
	ShuffleAnswers(g.question);
	g.lifeline = " ";
	MainPart(g);
}

void GetQuestionsForCurrentGame(Game& g)
{
	g.qList = QuestionsForGame(g.category);
}

Question GetQuestionForLevel(Game& g)
{
	int qCount = g.qList.qPerLevel[g.level - 1];
	QuestionsForLevel(g);

	// generating random number within the range of the count of the available questions
	srand((unsigned)time(NULL));
	int randomQ =  (rand() % qCount);
	string qId = g.qIdsForLevel[randomQ];
	return *FindQuestionById(qId);
}

void QuestionsForLevel(Game& g)
{
	g.qIdsForLevel.clear();
	for (auto& q : g.qList.list)
	{
		if (ConvertStringToInt(q.level) == g.level)
		{
			g.qIdsForLevel.emplace_back(q.id);
		}
	}
}

//void Heading()
//{
//	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
//		<< "\tPlayer: " << player << "          Level: " << q.level << "              Category : "<< categGame << "            Question for $" << prizes[level - 1] << "\n"
//		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
//}

void MainPart(Game& g)
{
	DisplayQ(g);

	if (g.lifeline != "")
	{
		cout << g.lifeline;
	}

    string input;
	cout << "\n\tWhat would you like to do? (S - give an answer, "
		<< "\n\tL - use a lifeline, Q - to quit the game): ";
	cin >> input;
	while (input != "L" && input != "Q" && input != "S")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}
	
	if (input == "L")
	{
		ChooseLifeline(g);
	}
	if (input == "Q")
	{
		QuitGame(g);
	}
	if (input == "S")
	{
		GiveAnswer(g);
	}

	//g.lifeline = " ";
}

void GiveAnswer(Game& g)
{
	clearScreen();
	Question& q = g.question;
	DisplayQ(g);
	int indexOfRightAnswer = FindIndexOfRightAnswer(q);
	string rightAnswer;
	if (indexOfRightAnswer == 0)
	{
		rightAnswer = "A";
	}
	if (indexOfRightAnswer == 1)
	{
		rightAnswer = "B";
	}
	if (indexOfRightAnswer == 2)
	{
		rightAnswer = "C";
	}
	if (indexOfRightAnswer == 3)
	{
		rightAnswer = "D";
	}
	
	string print = "\n\tChoose your answer(";

	if (q.answers[0] != "")
	{
		print += "A, ";
	}
	if (q.answers[1] != "")
	{
		print += "B, ";
	}
	if (q.answers[2] != "")
	{
		print += "C, ";
	}
	if (q.answers[3] != "")
	{
		print += "D, ";
	}
	print += "0 - other): ";
	cout << print;
	string input;
	cin >> input;
	while (input != "A" && input != "B" && input != "C" && input != "D" && input != "0")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}

	if (input == rightAnswer)
	{
		NextLevel(g);
	}
	else if (input == "0")
	{
		clearScreen();
		MainPart(g);
	}
	else
	{
		LostGame(g, rightAnswer);
	}

}

void LostGame(Game& g, string rightAnswer)
{
	clearScreen();
	cout << "\n\n\t\t\tWrong answer! Sorry, you lost the game!\n\n"
		<< "\t\tThe right answer was " << rightAnswer << ") " << g.question.rigthAnswer << ".\n\n"
		<< "\t\tYour earnings are: $" << g.wonMoney << "!\n\n";
	pressAnyKeyToContinueSimulation();
	clearScreen();
	Homepage();
}

void NextLevel(Game& g)
{
	// the player is sure to get the first guarantee sum when passed level 4
	if (g.level == 4)
	{
		g.wonMoney = g.prizes[g.level - 1];
	}

	// the player is sure to get the second guarantee sum when passed level 7
	if (g.level == 7)
	{
		g.wonMoney = g.prizes[g.level - 1];
	}

	// if the 10th levevl is successfully passed, the player gets the big prize and the game ends
	if (g.level == 10)
	{
		g.wonMoney = g.prizes[g.level - 1];
		End(g);
	}

	clearScreen();
	cout << "\n\n\t\t\tCongratulations! You won $" << g.prizes[g.level - 1] << "!\n\n";
	g.level++;
	pressAnyKeyToContinueSimulation();
	clearScreen();
	NewGame(g);
}

void DisplayQ(Game& g)
{
	Question q = g.question;
	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\tPlayer: " << g.player << "          Level: " << g.level << "              Category : " << g.category << "            Question for $" << g.prizes[ConvertStringToInt(q.level) - 1] << "\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

	cout << "\t " << g.level << ". " << q.body << endl << endl; //<< "\t";

	cout << "\tA) " << q.answers[0] << "                 B) " << q.answers[1] << endl << endl
		<< "\tC) " << q.answers[2] << "                 D) " << q.answers[3] << endl << endl;
	/*
	if (q.answers[0] != "")
	{
		cout << "A) ";
	}
	else
	{
		cout << "   ";
	}
	cout << q.answers[0] << "                 ";
	if (q.answers[1] != "")
	{
		cout << "B) ";
	}
	else
	{
		cout << "   ";
	}
	cout << q.answers[1] << endl << endl << "\t";

	if (q.answers[2] != "")
	{
		cout << "C) ";
	}
	else
	{
		cout << "   ";
	}
	cout << q.answers[2] << "                 ";
	if (q.answers[3] != "")
	{
		cout << "D) ";
	}
	cout << q.answers[3] << endl << endl;*/
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
	return -1;
}

void Lifeline50(Game& g)
{
	Question& q = g.question;
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
			else if (randomN == q.answers.size() - 1)
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

	g.life50 = false;
}

void LifelinePhoneAFriend(Game& g)
{
	Question q = g.question;
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
		"Hello " + g.player + ", I think the right answer is " + answer ,
		"Hey, Big " + g.player.substr(0, 1) + ", the right answer is " + answer ,
		"Hii, darling, I am so honoured to be your choice to call! In my opinion, the right answer is " +  answer,
		"The answer you are looking for is " + answer,
		"Hmmm, I'm not really sure, but I think it is " + answer,
		"This is not really my strong side, but I am pretty sure it's " + answer,
		"The right answer is " + answer,
		"Oh, " + g.player + ", but that's so easy! It's " + answer,
		"Hey, buddy, I think the answer is " + answer + " I hope you win the game!",
		"Hmm.. I am sorry, I can't think of anything right now, umm well..  /Time is up/"
	};

	srand((unsigned)time(NULL));
	int randomN = (rand() % calls.size());
	g.lifeline =  "\n\t" + calls[randomN] + "\n";
	g.lifeFriend = false;
}

void LifelineAskAudience(Game& g)
{
	g.lifeline = "";
	g.lifeAudience = false;
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
	int randomN = (rand() % 10);

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

void ChooseLifeline(Game& g)
{
	clearScreen();
	DisplayQ(g);

	string input;
	string printLifelines = "\n\tChoose a lifelife to use (";
	if (!g.life50 && !g.lifeAudience && !g.lifeFriend)
	{
		g.lifeline = "\n\tSorry, you've used all of your lifelines already.\n";
		clearScreen();
		MainPart(g);
	}

	if (g.life50 && g.lifeAudience && g.lifeFriend)
	{
		printLifelines =  "\n\tChoose a lifelife to use (X - 50/50, Y - Ask the Audience,\n\tZ - Phone a Friend, 0 - decline): ";
	}
	else
	{
		if (g.life50)
		{
			printLifelines += "X - 50 / 50, ";
		}
		if (g.lifeAudience)
		{
			printLifelines += "Y - Ask the Audience, ";
		}
		if (g.lifeFriend)
		{
			printLifelines += "Z - Phone a Friend, ";
		}
		printLifelines += "0 - decline): ";
	}
	
	cout << printLifelines;
	cin >> input;
	while ((input != "X" || input == "X" && !g.life50) &&
		(input != "Y" || input == "Y" && !g.lifeAudience) && 
		(input != "Z" || input == "Z" && !g.lifeFriend) && input != "0")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}

	clearScreen();
	if (input == "X")
	{
		Lifeline50(g);
		MainPart(g);
	}
	if (input == "Y")
	{
		LifelineAskAudience(g);
		MainPart(g);
	}
	if (input == "Z")
	{
		LifelinePhoneAFriend(g);
		MainPart(g);
	}
	if (input == "0")
	{
		MainPart(g);
	}
	
}

void QuitGame(Game& g)
{
	int level = g.level;
	string input;
	cout << "\n\n\tAre you sure you want to quit the game? (y/n): ";
	cin >> input;
	while (input != "y" && input != "n")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}
	clearScreen();
	if (input == "y")
	{
		if (level == 1)
		{
			g.wonMoney = 0;
		}
		else
		{
			g.wonMoney = g.prizes[level - 2];
		}

		End(g);
	}
	else
	{
		MainPart(g);
	}
}

void End(Game& g) 
{
	clearScreen();
	if (g.wonMoney == 100000)
	{
		cout << "\n\n\t\t\tCONGRATULATIONS!!!! " << g.player << ", you are the BIG WINNER!"
			<< "\n\t\t YOU WIN $100 000!!\n"
			<< "\n\t\t\t YOUR GAME WAS AWESOME!\n\n";
	}
	else if (g.wonMoney == 0)
	{
		cout << "\n\n\t\t\tSorry, " << g.player << ", you quitted too early."
			<< "\n\t\t\t You won nothing.\n\n";
	}
	else
	{ 
		cout << "\n\n\t\t\tCongratulations, " << g.player << "! It was a great game!"
			<< "\n\t\t\t You've won $" << g.prizes[g.level - 2] << "!\n\n";
	}

	pressAnyKeyToContinueSimulation();
	clearScreen();
	Homepage();
}