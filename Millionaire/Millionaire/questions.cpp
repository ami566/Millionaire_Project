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
	DeleteQuestion(questions, q, ' ');

	string input;
	
	cout << "\n\t\t  Fill out the following fields about the question:\n"
		<< "\t\t//Please refrain using these symbols: '|' and '&'. //\n\n"
		<< "\t!!! If you don't want to edit the field you are on, type '@!'\n "
		<< "\tand the original value would remain, otherwise just type your new entry!!!\n";

	cout << "\n\n\t  ID: " << q.id << " (Not changeable)";
	cout << "\n\t  Difficulty level: " << q.level << " (Not changeable)";
	cout << "\n\t  Category: ";
	cin.ignore();
	getline(cin, input);
	if (input != "@!")
	{
		q.category = input;
	}
	cout << "\t  Question: ";
	getline(cin, input);
	if (input != "@!")
	{
		q.body = input;
	}
	cout << "\t  Answer option #1: ";
	getline(cin, input);
	if (input != "@!")
	{
		q.answers[0] = input;
	}
	cout << "\t  Answer option #2: ";
	getline(cin, input);
	if (input != "@!")
	{
		q.answers[1] = input;
	}
	cout << "\t  Answer option #3: ";
	getline(cin, input);
	if (input != "@!")
	{
		q.answers[2] = input;
	}
	cout << "\t  Answer option #4: ";
	getline(cin, input);
	if (input != "@!")
	{
		q.answers[3] = input;
	}
	cout << "\t  Right answer: ";
	getline(cin, input);
	if (input != "@!")
	{
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
	// we open the text file with the trunc option and then close it to delete its contents
	std::fstream file;
	file.open(filename, std::fstream::out | std::fstream::trunc);
	file.close();
	// now we rewrite the file
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
	int count = 0;
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

Question GetQuestionFromInput(vector<Question>& questions)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	string answer;
	Question q;
	cout << "\n\t\t  Fill out the following fields about the question:\n"
	     << "\t\t//Please refrain using these symbols: '|' and '&'. //\n\n";

	cout << "  Choose from the already available categories or type a new one:\n   | ";
	for (auto& item : GetCategories(questions))
	{
		cout << item << " | ";
	}
	cout << "\n\n  Category: ";
	cin.ignore();
	getline(cin, q.category);
	cout << "  Difficulty level (1 - 10): ";
	getline(cin, q.level);
	cout << "  Question: ";
	getline(cin, q.body);
	cout << "  Answer option #1 (Right answer): ";
	getline(cin, q.rigthAnswer);
	q.answers.emplace_back(q.rigthAnswer);
	cout << "  Answer option #2: ";
	getline(cin, answer);
	q.answers.emplace_back(answer);
	cout << "  Answer option #3: ";
	getline(cin, answer);
	q.answers.emplace_back(answer);
	cout << "  Answer option #4: ";
	getline(cin, answer);
	q.answers.emplace_back(answer);
	q.id = to_string(rand());
	AddQuestionToList(questions, q);
	return q;
}

vector<string> GetCategories(vector<Question>& questions)
{
	vector<string> categories;
	bool containsCategory = false;
	for (auto& q : questions)
	{
		for (auto& c : categories)
		{
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
	// (which means there aren't questions from this category for that level)
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

