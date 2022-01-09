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

Question* FindQuestionById(std::string id);

void FillQuestions();

void AddQuestionToFile(Question q);

void DisplayQuestions(std::string keyword);

void EditQ(Question q);

void PrintQ(Question q);

void PrintWholeQ(Question q);

void RewriteFile(std::string fileNum);

std::string returnStringToLower(std::string s);

void stringToLower(std::string &s);

Question GetQuestionFromInput();

std::vector<std::string> GetCategories();

#endif	