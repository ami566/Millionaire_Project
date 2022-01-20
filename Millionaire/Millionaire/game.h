#pragma once
#ifndef GAME_H
#define GAME_H
#include "questions.h"
#include <iostream>
#include <vector>

struct Game {
	int level = 1;
	std::string category;
	std::string player;
	std::vector<std::string> qIdsForLevel;
	QuestionsList qList;
	Question question;
	bool life50 = true;
	bool lifeFriend = true;
	bool lifeAudience = true;
	std::string lifeline = "";
	const int prizes[10] = { 500, 1500, 3000, 5000, 10000, 15000, 25000, 50000, 70000, 100000 };
	int wonMoney = 0;
};

void Begin(std::vector<Question>& questions);
void NewGame(Game& g);
void GetQuestionsForCurrentGame(Game& g);
void QuestionsForLevel(Game& g);
Question GetQuestionForLevel(Game& g);
//void Heading();
void ShuffleAnswers(Question& q);
void MainPart(Game& g);
void Lifeline50(Game& g);
void LifelinePhoneAFriend(Game& g);
void LifelineAskAudience(Game& g);
void DisplayQ(Game& g);
void GiveAnswer(Game& g);
// for 'Call a friend' and 'Ask Audience' lifelines
int IndexOfAnswerForLifeline(Question& q);
void NextLevel(Game& g);
void LostGame(Game& g, std::string rightAnswer);
void ChooseLifeline(Game& g);
void QuitGame(Game& g);
void End(Game& g);
int FindIndexOfRightAnswer(Question& q);

#endif