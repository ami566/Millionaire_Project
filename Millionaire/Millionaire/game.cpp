#include "game.h"
#include "manual_functions.h"
#include "rules.h"
#include "hpfunctions.h"
#include "questions.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

void Begin(vector<Question>& questions)
{
	Game game;
	// print the heading part
	cout << "\n\n\t\t\tWELCOME TO 'WHO WANTS TO BE A MILLIONAIRE' - THE QUIZ GAME!\n\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
		<< "\tHow would you like to be adressed as? (Enter a name): ";
	cin.ignore();

	getline(cin, game.player); // to get the player's name

	cout << "\n\n\t\t\tChoose a category to play in: \n\n";

	// gets and then displayes all of the present categories, available to play in
	vector<string> categories = GetCategories(questions);
	int i = 0;
	for (; i < categories.size(); i++)
	{
		cout << "\t\t" << i + 1 << ". " << categories[i] << endl;
	}
	cout << "\n\t\t" << i + 1 << ". All categories"  << endl;

	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\tDISCLAIMER: If the category of your choice does not have enough questions to run for the game, then a \n"
		<< "\trandom question from the rest of the categories would be chosen at the same difficulty level. \n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	cout << "\n\tType the number of your chosen category (to go back, type 'M'): ";
	
	string input;
	cin >> input;

	if (input=="M")
	{
		GoBackToMain();
	}

	int categoryNum = ConvertStringToInt(input);
	// to validate the input
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

	// adds the last category, which basically includes all of the questions 
	if (categoryNum == i + 1)
	{
		game.category = "All";
	}
	else
	{
		game.category = categories[categoryNum-1];
	}

	game.qList.list = questions;
	clearScreen();
	RulesShort();
	pressAnyKeyToContinueSimulation();
	clearScreen();
	GetQuestionsForCurrentGame(game);
	NewGame(game);
}

void NewGame(Game& g)
{
	g.question = GetQuestionForLevel(g);     // so the random question gets "generated"
	ShuffleAnswers(g.question);              // to shuffle all of the answers
	g.lifeline = " ";                        // to clear the lifeline for the next level
	MainPart(g);
}

void GetQuestionsForCurrentGame(Game& g)
{
	g.qList = QuestionsForGame(g.qList.list, g.category);
}

Question GetQuestionForLevel(Game& g)
{
	int qCount = g.qList.qPerLevel[g.level - 1];
	QuestionsForLevel(g);

	// generating random number within the range of the count of the available questions
	srand((unsigned)time(NULL));
	int randomQ =  (rand() % qCount);
	string qId = g.qIdsForLevel[randomQ];
	return *FindQuestionById(g.qList.list, qId);
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

void MainPart(Game& g)
{
	DisplayQ(g);

	// to print the lifeline, if such has been previously called
	if (g.lifeline != "")
	{
		cout << g.lifeline;
	}

    string input;
	cout << "\n\tWhat would you like to do? (S - give an answer, "
		<< "\n\tL - use a lifeline, Q - to quit the game): ";
	cin >> input;
	// to validate the input
	while (input != "L" && input != "Q" && input != "S")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}
	
	// depending on the received from the console input, the respective function is called
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
	
	string print = "\n\tChoose your answer (";
	// to display the letters of the not empty answers
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
	print += "0 - decline): ";
	cout << print;
	string input;
	cin >> input;
	// to validate the input
	while (input != "A" && input != "B" && input != "C" && input != "D" && input != "0")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}

	// depending on the received from the console answer, the game is either switched to the next 
	// level, lost, or the player has decided to do something else, rather than give answer
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
	// prints the heading
	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\tPlayer: " << g.player << "          Level: " << g.level << "              Category : " << g.category << "            Question for $" << g.prizes[g.level - 1] << "\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	// prints the question
	cout << "\t " << g.level << "."; // << q.body << endl << endl;
	int length = q.body.size();
	int index = 0;
	
	cout << " " << q.body << endl << endl;
	//
	//if (length <= 100)
	//{
	//	cout << " " << q.body << endl << endl;
	//}
	//else
	//{
	//	while (length > 10)
	//	{
	//		cout << " " << q.body.substr(index, 100) << "\n\t"; // ??? why isn't this working properly
	//		length -= 100;
	//		index += 100;
	//	}
	//	if (index < length)
	//	{
	//		cout << " " << q.body.substr(index, q.body.size()) << "\n";
	//	}
	//}
	int spaces = 20; // set the default space place between two answers in a line to be 20 spaces 
	int spaces2 = spaces;

	// if either answer 1 or 3 is longer than the other, we calculate the difference between their 
	// lengths and add it as spaces to the shorter one  
	if (q.answers[0].size() < q.answers[2].size())
	{
		spaces += q.answers[2].size() - q.answers[0].size();
	}
	else
	{
		spaces2 += q.answers[0].size() - q.answers[2].size();
	}
	// print the answers
	cout << "\t A) " << q.answers[0] << setw(spaces) << "B) " << q.answers[1] << endl << endl
		<< "\t C) " << q.answers[2] << setw(spaces2) << " D) " << q.answers[3] << endl << endl
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
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

	string empty = ""; // to use when removing an answer

	int randomN = (rand() % 4); // generating random digit from 0 to 3 which would be the index of the first answer that would be removed

	// if the generated random digit happens to be the same as the right answer, which could not be removed
	// then we move the random digit by one to the left. If however it happens to be the first value and moving to left means 
	// going out of the the array, we change the the random digit to the last one, i.e in this case 3
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

	randomN = (rand() % 4); // generating random digit for the second answer that would be eliminated

	// proceeding to do the same check as for the first one, however this time the random digit could 
	// also fall to an empty answer, and that too have to be checked and considered.
	// So if the digit we have gotten could not remain the same and also cannot be moved to the left
	// we move it to the right by 1 (+ 1) and there won't be any problems, since there is only one right and one empty answer
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

	g.life50 = false;  // to mark the flag of this lifeline false (i.e lifelife Ask Audience is now used)
}

void LifelinePhoneAFriend(Game& g)
{
	Question q = g.question;
	// to get the random generated with conditions depending on the level index of the answer that is 
	// to have the greatest value to show
	int index = IndexOfAnswerForLifeline(q);
	string letter; // to store the letter of the answer that is to be shown
	// switch-case is used to find the letter of the answer that is to be shown
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

	// vector that holds some "calls" that the player can receive by a friend
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
	int randomN = (rand() % calls.size());              // to get a random "call by a friend" from the vector
	g.lifeline =  "\n\t" + calls[randomN] + "\n";       // to save the line that is to be shown to the user
	g.lifeFriend = false;                               // to mark the flag of this lifeline false (i.e lifelife Ask Audience is now used)
}

void LifelineAskAudience(Game& g)
{
	// to get the random generated with conditions depending on the level index of the answer that is 
	// to have the greatest value to show
	int index = IndexOfAnswerForLifeline(g.question);
	
	// this array will be used to hold the random generated percents for the audience vote
	// using array, since the values would be easier to sort if needed
	int* percents = new int[4];

	srand((unsigned)time(NULL));
	
	// if all the answers are present (i.e lifeline 50/50 hasn't been used on this question previously)
	// 4 different values which sum is 100 (to complete the 100%) need to be generated
	if (g.question.answers[0] != "" && g.question.answers[1] != "" && g.question.answers[2] != "" && g.question.answers[3] != "") 
	{
		// wholly random algorithm is used to populate the array with some values to complete the 100%
		percents[0] = (rand() % 70);
		percents[1] = (rand() % (90 - percents[0]));
		percents[2] = (rand() % (100 - percents[0] - percents[1]));
		percents[3] = 100 - (percents[0] + percents[1] + percents[2]);

		// we sort the arrays so we know for sure that the first value is the greatest among the rest
		// so it's easier on a later stage to give that biggest value to the answer that is received to be
		// the chosen one, could be either right or wrong
		sortIntArr(percents, 4);
	}
	// if the 50/50 lifeline is used and there are empty answers, there would be needed only 2 numbers with sum 100 to be generated
	else
	{
		percents[0] = 51 + (rand() % 40); // so we know that the first value holds the biggest value for sure
		percents[1] = 100 - percents[0];
	}
	
	// if the chosen answer is not the first one, we swap the values to the first one and to the one which has to hold the biggest value
	if (index != 0)
	{
		SwapInt(percents[0], percents[index]);
	}

	if (g.question.answers[0] == "" || g.question.answers[1] == "" || g.question.answers[2] == "" || g.question.answers[3] == "")
	{
		// in case there are empty answers, the one left that is not the chosen one, might be at any position
		// so we find it and give it the second value that completes the 100 % with the chosen one
		if (g.question.answers[0] != "" && index != 0)
		{
			SwapInt(percents[0], percents[1]);
		}
		if (g.question.answers[2] != "" && index != 2)
		{
			SwapInt(percents[2], percents[1]);
		}
		if (g.question.answers[3] != "" && index != 3)
		{
			SwapInt(percents[3], percents[1]);
		}
	}

	// here we make the string that is to be shown to the user with the answers' letters and percents
	string print = "\n\tAudience vote: ";
	if (g.question.answers[0] != "")
	{
		print += "  A - " + to_string(percents[0]) + "%        ";
	}

	if (g.question.answers[1] != "")
	{
		print += "B - " + to_string(percents[1]) + "%        ";
	}

	if (g.question.answers[2] != "")
	{
		print += "C - " + to_string(percents[2]) + "%        ";
	}

	if (g.question.answers[3] != "")
	{
		print += "D - " + to_string(percents[3]) + "%        ";
	}

	delete[] percents;               // to free the heap memory that was used to store the percents
	g.lifeline = print + "\n\n";     // to save the line that is to be shown to the user
	g.lifeAudience = false;          // to mark the flag of this lifeline false (i.e lifelife Ask Audience is now used)
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

	// to print a message of all of the lifelines have been used
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
		// these conditions are so a lifeline that has already been used, to not be printed again
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
	// checks if the input is valid, that is either any one of the symbols that represent the lifelines (X, Y or Z)
	// or even if they have chosen one of those, but the lifeline has already been used
	while ((input != "X" || input == "X" && !g.life50) &&
		(input != "Y" || input == "Y" && !g.lifeAudience) && 
		(input != "Z" || input == "Z" && !g.lifeFriend) && input != "0")
	{
		cout << "\t\aInvalid input! Please type your choice again: ";
		cin >> input;
	}

	clearScreen();
	// to call the respective function for the chosen lifeline
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
			g.wonMoney = g.prizes[level - 2]; // gets the last sum won, i.e the money from the previous level
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
	
	if (g.wonMoney == g.prizes[9]) // if the money are equal to 100000, then the game has been won
	{
		cout << "\n\n\t\t\tCONGRATULATIONS!!!! " << g.player << ", you are the BIG WINNER!"
			<< "\n\t\t\t\t YOU WIN $100 000!!\n"
			<< "\n\t\t\t\t\t YOUR GAME WAS AWESOME!\n\n";
	}
	// if there aren't any money won, then the game has been quitted before completing the first level
	else if (g.wonMoney == 0)
	{
		cout << "\n\n\t\t\tSorry, " << g.player << ", you quitted too early."
			<< "\n\t\t\t\t You won nothing.\n\n";
	}
	// any other case, when quitted the game, this is what would be shown to the player
	else
	{ 
		cout << "\n\n\t\t\tCongratulations, " << g.player << "! It was a great game!"
			<< "\n\t\t\t\t You've won $" << g.prizes[g.level - 2] << "!\n\n";
	}

	pressAnyKeyToContinueSimulation();
	clearScreen();
	Homepage();
}