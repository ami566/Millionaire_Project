#include "questions.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h> 
//#include <boost/algorithm/string.hpp>

using namespace std;

vector<Question> questions ;
string filename;

void FillQuestions()
{
	// checks if the questions vector is empty and if it is, we populate it with the questions from the text files
	// the questions vector can already contain elements if we have called the GetQuestions function previously during the program
	if (questions.empty())
	{
		GetQuestions();
	}
}

vector<Question> Questions() 
{
	FillQuestions();
	return questions;
}

void GetQuestions()
{
	questions.clear();
	string buffer;
	
	for (int i = 1; i <= 10; i++)
	{
		filename = "level" + to_string(i) + ".txt";
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
				AddQuestionToList(q); // adds the question to the questions list
			}
		}
		myFile.close();
	}
}

void AddQuestionToFile(Question q)
{
	filename = "level" + q.level +".txt";
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

void EditQ(Question q)
{
	int index = 0;
	for (auto& item : questions)
	{
		if (item.id==q.id)
		{
			break;
		}
		index++;
	}

	questions.erase(questions.begin()+index);

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
	AddQuestionToList(q);
	RewriteFile(q.level);
}

void RewriteFile(string level)
{
	filename = "level" + level + ".txt";
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

void AddQuestionToList(Question q)
{
	questions.emplace_back(q);
}

void stringToLower(string& s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
}

string returnStringToLower(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

void DisplayQuestions(string keyword)
{
	FillQuestions();
	
	if (keyword == "")
	{
		for (auto& q : questions)
		{
			PrintQ(q);
		}
		return;
	}
	
	stringToLower(keyword);
	for (auto& q : questions)
	{
		string answers;
		for (auto& a : q.answers)
		{
			answers += a + " ";
		}
		stringToLower(answers);
		
		if (returnStringToLower(q.category).find(keyword)!= string::npos || returnStringToLower(q.body).find(keyword) != string::npos || 
			returnStringToLower(q.body).find(keyword) != string::npos || answers.find(keyword) != string::npos)
		{
			PrintQ(q);
		}
	}
	
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

Question* FindQuestionById(string id)
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

Question GetQuestionFromInput()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	string answer;
	Question q;
	cout << "\n\t\t  Fill out the following fields about the question:\n"
	     << "\t\t//Please refrain using these symbols: '|' and '&'. //\n\n";

	cout << "  Choose from the already available categories or type a new one:\n   | ";
	for (auto& item : GetCategories())
	{
		cout << item << " | ";
	}
	cout << "\n\n  Category: ";
	cin.ignore();
	getline(cin, q.category);
	cout << "  Difficulty level: ";
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
	AddQuestionToList(q);
	return q;
}

vector<string> GetCategories()
{
	FillQuestions();

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
