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

// hasn't been tested yet
void GetQuestions()
{
	string buffer;
	Question q;
	for (int i = 1; i <= 10; i++)
	{
		filename = "level" + to_string(i) + ".txt";
		std::fstream myFile;
		myFile.open(filename, std::fstream::in);

		if (myFile.is_open()) {

			while (getline(myFile, buffer)) {
				int j = 0;
				while (j < buffer.size() && buffer[j] != '|') 
				{
					q.id += buffer[j++];
				}
				j++; // in order to skip the '|'
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
				
				string answers;
				// to get all the answers
				while (j < buffer.size() && buffer[j] != '|')
				{
					answers += buffer[j++];
				}
				j++;
				
				// to separate the different answer options and add them to the answers array of the question
				int k = 0;
				int answersNo = 0;
				string aOption;
				while (k<answers.size())
				{
					if (answers[k]=='&')
					{
						q.answers[answersNo] = aOption;
						aOption = "";
						answersNo++;
						continue;
					}
					aOption += answers[k++];
				}

				while (j < buffer.size()) 
				{
					q.rigthAnswer += buffer[j++];
				}
				questions.emplace_back(q);
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

void EditQuestion(Question q)
{
}

Question GetQuestionFromInput()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	string answer;
	Question q;
	cout << "\n\t  Fill out the following fields about the question:\n";
	cout << "\t//Please refrain using these symbols: '|' and '&'. //\n\n";
	cout << "Category: ";
	cin.ignore();
	getline(cin, q.category);
	cout << "Difficulty level: ";
	getline(cin, q.level);
	cout << "Question: ";
	getline(cin, q.body);
	cout << "Answer option #1 (Right answer): ";
	getline(cin, q.rigthAnswer);
	q.answers.emplace_back(q.rigthAnswer);
	cout << "Answer option #2: ";
	getline(cin, answer);
	q.answers.emplace_back(answer);
	cout << "Answer option #3: ";
	getline(cin, answer);
	q.answers.emplace_back(answer);
	cout << "Answer option #4: ";
	getline(cin, answer);
	q.answers.emplace_back(answer);
	q.id = to_string(rand());
	return q;
}

//vector<string> GetGategories(vector<Question> questions)
//{
//	return;
//}
