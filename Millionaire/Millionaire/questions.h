#pragma once
#ifndef QUESTIONS_H
#define QUESTIONS_H
#include <iostream>
#include <vector>

// declaring a Question structure so it's easier to access its different parts
struct Question {
	std::string id;
	std::string level;
	std::string body;
	std::string category;
	std::string rigthAnswer;
	std::vector<std::string> answers;
};

// declaring structure for easier access to particular questions, their category 
// and the count of questions available for each level
struct QuestionsList {
	std::vector<Question> list;
	std::string category;
	// in this array we will see how many questions available are there per level
	int qPerLevel[10] = { 0,0,0,0,0,0,0,0,0,0 };
};

// function to read and store all questions from the text files
std::vector<Question> GetQuestions();

// function to find a question from list (vector) of questions by given ID
Question* FindQuestionById(std::vector<Question>& questions, std::string id);

// function that adds (writes) a question to the needed text file (this depending on the level)
void AddQuestionToFile(Question q);

// function that adds question to given list (vector) of questions
void AddQuestionToList(std::vector<Question>& questions, Question q);

// function to display/print all of the questions that contain certain keyword
// or if not given, to display all of the questions, and to return their count
int DisplayQuestions(std::vector<Question>& questions, std::string keyword);

// function that allows the player to make changes to chosen question 
// which changes are later saved on the certain text file too
void EditQ(std::vector<Question>& questions, Question q);

// function that depending how called, can either remove a question from given
// list (vector) of questions, or can do that, and also remove the question from the text file where it's stored
void DeleteQuestion(std::vector<Question>& questions, Question q, char c);

// function that prints the ID and the body of a question (used when there are displayed questions for the player to edit)
void PrintQ(Question q);

// function that prints on the console all of the elements of the question
void PrintWholeQ(Question q);

// function that when called, deletes the content of given file and rewrites it with the added new information
void RewriteFile(std::vector<Question>& questions, std::string fileNum);

// function that reads the information for the question from the console and then adds the question to the given list
Question GetQuestionFromInput(std::vector<Question>& questions);

// function that checks if the input from the console is in the correct format
void ValidateInput(std::string& input, const std::string& valid1, const std::string& valid2, const std::string& errorM, const std::string& exit);

// function that returns list (vector) with the names of all different categories of questions from all files
std::vector<std::string> GetCategories(std::vector<Question>& questions);

// function that returns QuestionList type of object, that stores all of the questions for the current game
// i.e if the players choses to play with questions from certain category, the function returns all of the 
// questions that have the wanted category, else, it returns all of the available question
QuestionsList QuestionsForGame(std::vector<Question>& questions, std::string category);
#endif	