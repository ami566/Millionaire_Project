#include "questions.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <stdio.h>
#include <time.h> 

using namespace std;

vector<Question> questions ;
string filename;

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
				while (j < buffer.size() && buffer[j] != '&')
				{
					aOption += buffer[j++];
				}
				q.answers.emplace_back(aOption);
				aOption = "";
				j++;

				while (j < buffer.size() && buffer[j] != '&')
				{
					aOption += buffer[j++];
				}
				q.answers.emplace_back(aOption);
				aOption = "";
				j++;

				while (j < buffer.size() && buffer[j] != '&')
				{
					aOption += buffer[j++];
				}
				q.answers.emplace_back(aOption);
				aOption = "";
				j++;
				
				while (j < buffer.size() && buffer[j] != '|')
				{
					aOption += buffer[j++];
				}
				q.answers.emplace_back(aOption);
				aOption = "";
				j++;

				while (j < buffer.size()) 
				{
					q.rigthAnswer += buffer[j++];
				}
				questions.emplace_back(q); // adds the question to the questions list
			}
			
		}
		myFile.close();
	}
}

void AddQuestionToFile(Question &q)
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

void EditQuestion(Question q)
{

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
	questions.emplace_back(q);
	return q;
}

vector<string> GetCategories()
{
	// checks if the questions vector is empty and if it is, we populate it with the questions from the text files
	// the questions vector can already contain elements if we have called the GetQuestions function previously during the program
	if (questions.empty())
	{
		GetQuestions();
	}
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
