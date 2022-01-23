#pragma once
#include "questions.h"
// homepageFunctions header
#ifndef HPFUNCTIONS_H
#define HPFUNCTIONS_H

// function that is used for the main page
void Homepage();

// function that is called when the user wants to start a new game 
void Play(std::vector<Question>& questions);

// function that is called when the user wants to see the detailed rules
void Rules();

// function that is called when the user wants to add new question to the game
void AddQuestion(std::vector<Question>& questions);

// function that is called when the user is editing an existing question
void EditQuestion(std::vector<Question>& questions, Question q);

// function that is called when the user wants to edit an existing question
void EditQuestionHome(std::vector<Question>& questions);

// function that is called when the input is not in the valid format
void InvalidInput();



#endif