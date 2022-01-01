#include "questions.h"
#include <iostream>
#include <vector>
using namespace std;

vector<Question> questions;


vector<Question> GetQuestions()
{

	return questions;
}

void AddQuestionToFile(Question q)
{
}

void EditQuestion(Question q)
{
}

Question GetQuestionFromInput()
{
	string answer;
	Question q;
	cout << "Fill out the following fields about the question:\n";
	cout << "// Please refrain using these symbols: '|' and '&' //\n\n";
	cout << "Category: ";
	cin >> q.category;
	cout << "\nQuestion: ";
	cin >> q.body;
	cout << "\nAnswer option #1 (Right answer): ";
	cin >> q.rigthAnswer;
	q.answers.emplace_back(q.rigthAnswer);
	cout << "\nAnswer option #2: ";
	cin >> answer;
	q.answers.emplace_back(answer);
	cout << "\nAnswer option #3: ";
	cin >> answer;
	q.answers.emplace_back(answer);
	cout << "\nAnswer option #4: ";
	cin >> answer;
	q.answers.emplace_back(answer);

	return Question();
}

vector<string> GetGategories(vector<Question> questions)
{}
