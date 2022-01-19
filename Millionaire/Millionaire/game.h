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
void Lifeline50(Question& q);
void LifelinePhoneAFriend(Question& q);
void LifelineAskAudience(Question& q);
void DisplayQ(Question& q);
// for 'Call a friend' and 'Ask Audience' lifelines
int IndexOfAnswerForLifeline(Question& q);
void ChooseLifeline();
void QuitGame();
void End();

#endif