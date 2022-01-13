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

struct QuestionsList {
	std::vector<Question> list;
	std::string category;

	// in this array we will see how many questions available are there per level
	int qPerLevel[10] = { 0,0,0,0,0,0,0,0,0,0 };
};

void GetQuestions();

std::vector<Question> Questions();

Question* FindQuestionById(std::string id);

void FillQuestions();

void AddQuestionToFile(Question q);

void AddQuestionToList(Question q);

void DisplayQuestions(std::string keyword);

void EditQ(Question q);

void DeleteQuestion(Question q, char c);

void PrintQ(Question q);

void PrintWholeQ(Question q);

void RewriteFile(std::string fileNum);

Question GetQuestionFromInput();

std::vector<std::string> GetCategories();

QuestionsList QuestionsForGame(std::string category);
#endif	