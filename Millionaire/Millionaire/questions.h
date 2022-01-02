#pragma once
#ifndef QUESTIONS_H
#define QUESTIONS_H
#include <iostream>
#include <vector>

struct Question {
	std::string id;
	std::string level;
	std::string body;
	std::string category;
	std::string rigthAnswer;
	std::vector<std::string> answers;
};

void GetQuestions();

void AddQuestionToFile(Question q);

void EditQuestion(Question q);

Question GetQuestionFromInput();

//vector<string> GetGategories(vector<Question> questions);

#endif	