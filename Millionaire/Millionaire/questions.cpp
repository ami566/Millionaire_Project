#include "questions.h"
#include "manual_functions.h"
#include "game.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h> 


using namespace std;

vector<Question> GetQuestions()
{
	vector<Question> questions;
	string buffer;
	
	for (int i = 1; i <= 10; i++)
	{
		string filename = "level" + to_string(i) + ".txt";
		std::fstream myFile;
		myFile.open(filename, std::fstream::in);

		if (myFile.is_open()) {

			while (getline(myFile, buffer)) {
				Question q;
				int j = 0;
				while (j < buffer.size() && buffer[j] != '|') 
				{
					q.id += buffer[j++];
				}
				j++; // in order to skip the '|'
				q.level = to_string(i);
				while (j < buffer.size() && buffer[j] != '|')
				{
					q.category += buffer[j++];
				}
				j++;
				while (j < buffer.size() && buffer[j] != '|')
				{
					q.body += buffer[j++];
				}
				j++;
				
				// to get all the answers
				string aOption;
				while (j < buffer.size() && buffer[j] != '|')
				{
					if (buffer[j]=='&')
					{
						q.answers.emplace_back(aOption);
						aOption = "";
						j++; 
						continue;
					}
					aOption += buffer[j++];
				}
				q.answers.emplace_back(aOption);
				j++;

				while (j < buffer.size()) 
				{
					q.rigthAnswer += buffer[j++];
				}
				AddQuestionToList(questions, q); // adds the question to the questions list
			}
		}
		myFile.close();
	}
	return questions;
}

void AddQuestionToFile(Question q)
{
	string filename = "level" + q.level +".txt";
	std::fstream file;
	file.open(filename, std::fstream::out | std::fstream::app);
	// the question would be saved on the txt file in the following format:
	// id|category|question|answer&answer&answer&answer|right answer
	file << q.id << '|'
		<< q.category << '|'
		<< q.body << '|'
		<< q.answers[0] << '&'
		<< q.answers[1] << '&'
		<< q.answers[2] << '&'
		<< q.answers[3] << '|'
		<< q.rigthAnswer << '\n';
	file.close();
}

void EditQ(vector<Question>& questions, Question q)
{
	const string exit = "&|";   // the string if given as input, would mean the player wants to go back to the main panel
	const string valid1 = "|";  // to use for the validation since the text in the files is stored and read with these symbols as breakpoints
	const string valid2 = "&";  // same application as valid1
	const string errorM = "\a\tInvalid input, please try again: ";

	DeleteQuestion(questions, q, ' ');

	string input;
	const string noChange = "@!";
	
	cout << "\n\t\t  Fill out the following fields about the question:\n"
		<< "\t\t//Please refrain using these symbols: '|' and '&'. //\n\n"
		<< "\t!!! If you don't want to edit the field you are on, type '" << noChange <<"'.\n "
		<< "\tand the original value would remain, otherwise just type your new entry!!!\n";

	cout << "\n\n\t  ID: " << q.id << " (Not changeable)";
	cout << "\n\t  Difficulty level: " << q.level << " (Not changeable)";
	cout << "\n\t  Category: ";
	cin.ignore();
	getline(cin, input);
	if (input != noChange)
	{
		ValidateInput(input, valid1, valid2, errorM, exit);
		q.category = input;
	}
	cout << "\t  Question: ";
	getline(cin, input);
	if (input != noChange)
	{
		ValidateInput(input, valid1, valid2, errorM, exit);
		q.body = input;
	}
	cout << "\t  Answer option #1: ";
	getline(cin, input);
	if (input != noChange)
	{
		ValidateInput(input, valid1, valid2, errorM, exit);
		q.answers[0] = input;
	}
	cout << "\t  Answer option #2: ";
	getline(cin, input);
	if (input != noChange)
	{
		ValidateInput(input, valid1, valid2, errorM, exit);
		q.answers[1] = input;
	}
	cout << "\t  Answer option #3: ";
	getline(cin, input);
	if (input != noChange)
	{
		q.answers[2] = input;
	}
	cout << "\t  Answer option #4: ";
	getline(cin, input);
	if (input != noChange)
	{
		ValidateInput(input, valid1, valid2, errorM, exit);
		q.answers[3] = input;
	}
	cout << "\t  Right answer: ";
	getline(cin, input);
	if (input != noChange)
	{
		ValidateInput(input, valid1, valid2, errorM, exit);
		q.rigthAnswer = input;
	}
	AddQuestionToList(questions, q);
	RewriteFile(questions, q.level);
}

// if the DeleteQuestion() function is called with any char c, but white space,
// that means deletion of the question to both the questions list and the file it's stored, is needed
void DeleteQuestion(vector<Question>& questions, Question q, char c)
{
	int index = 0;
	for (auto& item : questions)
	{
		if (item.id == q.id)
		{
			break;
		}
		index++;
	}
	string level = q.level;
	questions.erase(questions.begin() + index);

	if (c != ' ')
	{
		RewriteFile(questions, level);
	}
}

void RewriteFile(vector<Question>& questions, string level)
{
	string filename = "level" + level + ".txt";
	// opens the text file with the trunc option and then closes it to delete its contents
	std::fstream file;
	file.open(filename, std::fstream::out | std::fstream::trunc);
	file.close();
	// to rewrite the file
	for (auto& q : questions)
	{
		if (q.level==level)
		{
			AddQuestionToFile(q);
		}
	}
}

void AddQuestionToList(vector<Question>& questions, Question q)
{
	questions.emplace_back(q);
}

int DisplayQuestions(vector<Question>& questions, string keyword)
{	
	int count = 0; // to store the count of the questions that would be displayed
	// if there isn't a keyword given, print all the questions
	if (keyword == "")
	{
		for (auto& q : questions)
		{
			PrintQ(q);
			count++;
		}
		return count;
	}
	
	stringToLower(keyword); // to not have case-sensitive search
	for (auto& q : questions)
	{
		string answers; // to get the answers in one string so it would be easier to go through them later on
		for (auto& a : q.answers)
		{
			answers += a + " ";
		}
		stringToLower(answers);
		
		if (returnStringToLower(q.category).find(keyword)!= string::npos || returnStringToLower(q.body).find(keyword) != string::npos || 
			returnStringToLower(q.body).find(keyword) != string::npos || answers.find(keyword) != string::npos)
		{
			PrintQ(q);
			count++;
		}
	}
	return count;
}

void PrintQ(Question q)
{
	cout << "  " << q.id << ": " << q.body << endl;
}

void PrintWholeQ(Question q)
{
	cout << "\t  Id: " << q.id << endl
		<< "\t  Difficulty level: " << q.level << endl
		<< "\t  Category: " << q.category << endl
		<< "\t  Question: " << q.body << endl
		<< "\t  Answer option #1: " << q.answers[0] << endl
		<< "\t  Answer option #2: " << q.answers[1] << endl
		<< "\t  Answer option #3: " << q.answers[2] << endl
		<< "\t  Answer option #4: " << q.answers[3] << endl
		<< "\t  Right answer: " << q.rigthAnswer << endl;
}

Question* FindQuestionById(vector<Question>& questions, string id)
{
	for (auto& q : questions)
	{
		if (q.id==id)
		{
			return &q;
		}
	}
	return  NULL;
}

void ValidateInput(string& input, const string& valid1, const string& valid2, const string& errorM, const string& exit)
{
	while (input.find(valid1) != string::npos || input.find(valid2) != string::npos)
	{
		if (input == exit)
		{
			GoBackToMain();
		}
		cout << errorM;
		getline(cin, input);
	}
}

Question GetQuestionFromInput(vector<Question>& questions)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	string input;
	const string exit = "&|";   // the string if given as input, would mean the player wants to go back to the main panel
	const string valid1 = "|";  // to use for the validation since the text in the files is stored and read with these symbols as breakpoints
	const string valid2 = "&";  // same application as valid1
	const string errorM = "\a  Invalid input, please try again: ";
	Question q;
	cout << "\n\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
		<< "\tDISCLAIMER: To exit at any time, type '" << exit << "' and you will return to the Hompepage, no changes \n"
		<< "\twould be saved. Otherwise, please refrain using these symbols: '" << valid1 << "' and '" << valid2 << "'.\n"
		<< "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	cout << "\t\t  Fill out the following fields about the question:\n";

	cout << "\tChoose from the already available categories or type a new one:\n   | ";
	int i = 0;
	for (auto& item : GetCategories(questions))
	{
		if (i == 10)
		{
			cout << endl;
			i = 0;
		}
		cout << item << " | ";
		i++;
	}
	cout << "\n\n  Category: ";
	cin.ignore();
	getline(cin, input);
	ValidateInput(input, valid1, valid2, errorM, exit);
	q.category = input;
	
	cout << "  Difficulty level (1 - 10): ";
	getline(cin, input);
	int level = ConvertStringToInt(input);
	while (level < 1 || level > 10 || level == -1)
	{
		if (input == exit)
		{
			GoBackToMain();
		}
		cout << errorM;
		getline(cin, input);
		level = ConvertStringToInt(input);
	}
	q.level = input;

	cout << "  Question: ";
	getline(cin, input);
	ValidateInput(input, valid1, valid2, errorM, exit);
	q.body = input;

	cout << "  Answer option #1 (Right answer): ";
	getline(cin, input);
	ValidateInput(input, valid1, valid2, errorM, exit);
	q.rigthAnswer = input;
	q.answers.emplace_back(q.rigthAnswer);

	cout << "  Answer option #2: ";
	getline(cin, input);
	ValidateInput(input, valid1, valid2, errorM, exit);
	q.answers.emplace_back(input);

	cout << "  Answer option #3: ";
	getline(cin, input);
	ValidateInput(input, valid1, valid2, errorM, exit);
	q.answers.emplace_back(input);

	cout << "  Answer option #4: ";
	getline(cin, input);
	ValidateInput(input, valid1, valid2, errorM, exit);
	q.answers.emplace_back(input);

	q.id = to_string(rand());

	AddQuestionToList(questions, q);
	cout << "\n\n  Question saved successfully!\n";
	return q;
}

vector<string> GetCategories(vector<Question>& questions)
{
	vector<string> categories;  // vector to store the categories' names
	bool containsCategory = false;
	for (auto& q : questions)
	{
		for (auto& c : categories)
		{
			// if the category of the question is already stored, we will just skip to the next one
			if (q.category==c)
			{
				containsCategory = true; 
				break;
			}
		}
		if (!containsCategory)
		{
			categories.emplace_back(q.category);
		}
		containsCategory = false;
	}
	return categories;
}

QuestionsList QuestionsForGame(vector<Question>& questions, string category)
{
	QuestionsList qList;
	Question q;
	qList.category = category;

	// to get all of the questions for the category chosen by the player
	for (int i = 0; i < questions.size(); i++)
	{
		q = questions[i];
		if (q.category == category)
		{
			qList.list.emplace_back(q);
			qList.qPerLevel[ConvertStringToInt(q.level) - 1] += 1;
		}
	}

	// with this loop we check if there are levels with zero questions 
	// (which means there aren't any questions from this category for the wanted level)
	// and if there is one (or more) found, then we get the rest of the 
	// questions for the same level but from different category
	for (int i = 0; i < 10; i++)
	{
		if (qList.qPerLevel[i] == 0)
		{
			for (int j = 0; j < questions.size(); j++)
			{
				q = questions[j];
				if (ConvertStringToInt(q.level) - 1 == i)
				{
					qList.list.emplace_back(q);
					qList.qPerLevel[i] += 1;
				}
			}
		}
	}

	return qList;
}

