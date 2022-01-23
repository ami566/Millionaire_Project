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

std::vector<Question> GetQuestions();

Question* FindQuestionById(std::vector<Question>& questions, std::string id);

void AddQuestionToFile(Question q);

void AddQuestionToList(std::vector<Question>& questions, Question q);

int DisplayQuestions(std::vector<Question>& questions, std::string keyword);

void EditQ(std::vector<Question>& questions, Question q);

void DeleteQuestion(std::vector<Question>& questions, Question q, char c);

void PrintQ(Question q);

void PrintWholeQ(Question q);

void RewriteFile(std::vector<Question>& questions, std::string fileNum);

Question GetQuestionFromInput(std::vector<Question>& questions);

void ValidateInput(std::string& input, const std::string& valid1, const std::string& valid2, const std::string& errorM, const std::string& exit);

std::vector<std::string> GetCategories(std::vector<Question>& questions);

QuestionsList QuestionsForGame(std::vector<Question>& questions, std::string category);
#endif	