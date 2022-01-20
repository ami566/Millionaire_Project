#pragma once
#include "questions.h"
// homepageFunctions header
#ifndef HPFUNCTIONS_H
#define HPFUNCTIONS_H

void Homepage();

void Play(std::vector<Question>& questions);

void Rules();

void AddQuestion(std::vector<Question>& questions);

void EditQuestion(std::vector<Question>& questions, Question q);

void EditQuestionHome(std::vector<Question>& questions);

void InvalidInput();

void GoBackToMain();

#endif