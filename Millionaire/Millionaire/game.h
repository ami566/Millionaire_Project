#pragma once
#ifndef GAME_H
#define GAME_H
#include "questions.h"
#include <iostream>
#include <vector>

// declaring a Game structure so it's easier to access all of its different parts
struct Game {
	int level = 1;                         // holds the level of the current game
	std::string category;                  // holds the category name of the chosen from the player category
	std::string player;                    // holds the player's name
	std::vector<std::string> qIdsForLevel; // holds the IDs of the questions for the current level
	QuestionsList qList;                   // holds all of the questions for the current game
	Question question;                     // holds the question for the current level
	bool life50 = true;                    // flags if lifeline 50/50 is used
	bool lifeFriend = true;                // flags if lifeline Phone A Friend is used
	bool lifeAudience = true;              // flags if lifeline Aks the Audience is used
	std::string lifeline = "";             // holds the text that would be displayed when used certain lifeline
	int wonMoney = 0;                      // holds the earnings of the player
	// array that holds all of the values (prizes) for the different questions
	const int prizes[10] = { 500, 1500, 3000, 5000, 10000, 15000, 25000, 50000, 70000, 100000 };
	
};

// function that is called when the game begins
void Begin(std::vector<Question>& questions);

// function that drives the main proccess of the current game, meaning, it's called for every level
void PlayGame(Game& g);

// function that saves all of the needed questions for the game to the structure holding the information for the current game
void GetQuestionsForCurrentGame(Game& g);

// function that saves all of the needed questions for the current level to the structure holding the information for the current game
void QuestionsForLevel(Game& g);

// function that gets random question from the questions list, to be used for the player to play
Question GetQuestionForLevel(Game& g);

// function that shuffles all of the answers of the question that is to be shown to the player
void ShuffleAnswers(Question& q);

// function that is called when chosen to play new game (here the category to play in is being chosen)
void MainPart(Game& g);

// function that eliminates two wrong answers from the given question
void Lifeline50(Game& g);

// function that simulates a "call" from a friend that says what the friend thinks is the right answer
void LifelinePhoneAFriend(Game& g);

// function that simulates the vote of the audience with percentages
void LifelineAskAudience(Game& g);

// function that when called, displays on the console the question and the answers for the current level
void DisplayQ(Game& g);

// function that is called when the player has chosen to "give answer", i.e to input on the console an answer 
// that the player think is the right one
void GiveAnswer(Game& g);

// function that returns the index of the answer that is chosen by different logic for the different levels 
// (used for 'Call a friend' and 'Ask Audience' lifelines)
int IndexOfAnswerForLifeline(Question& q);

// function that is called when the player has given the right answer to the question
// shows the earned money from the level
void NextLevel(Game& g);

// function that is called when the player gives wrong answer and loses the game
// it shows the right answer and the player's earnings
void LostGame(Game& g, std::string rightAnswer);

// function that when called, shows the available lifeline, and then calls the particular one when chosen, if not already used
void ChooseLifeline(Game& g);

// function that is called when the player decides to quit the game and calculates the player's earnings
void QuitGame(Game& g);

// function that is called when the player has quit the game or wins it, it displays the player's earnings on the console
void End(Game& g);

// function that find the index of the right answer of the given question
int FindIndexOfRightAnswer(Question& q);

#endif