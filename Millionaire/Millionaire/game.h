#pragma once
#ifndef GAME_H
#define GAME_H
#include "questions.h"
#include <iostream>
#include <vector>

void Begin();
void NewGame();
void GetQuestionsForCurrentGame();
void QuestionsForLevel();
Question GetQuestionForLevel();
void Heading();
void ShuffleAnswers(Question& q);
void MainPart(Question& q);

#endif