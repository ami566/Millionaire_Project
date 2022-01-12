#include "rules.h"
#include <iostream>
using namespace std;
void DisplayRules()
{
    cout << "\n\t\t\tWELCOME TO 'WHO WANTS TO BE A MILLIONAIRE' - THE QUIZ GAME!\n\n"
        << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
        << "\tGAME RULES\n\n"
        << "\tYou must answer 10 multiple-choice questions correctly in order to win the big prize - $100 000.\n\n"
        << "\tYou may quit at any time and keep your earnings till then. The question and four possible answers \n"
        << "\tare shown in advance before you can decide whether to quit or not. If you decide to play, then you\n"
        << "\thave to give the right answer to continue with the game. If at any stage, you give a wrong answer \n"
        << "\tyour earnings fall back to the  'guarantee point' - either $5000 or $25 000 - and your game is over.\n\n"
        << "\tThe questions are with increasing difficulty with the first one being the easiest and the 10th one -\n"
        << "\tthe most difficult. At the beginning of every new game, you can select a specific category for your\n"
        << "\tquestions to be from or you can choose to play with questions from all categories. If your chosen \n"
        << "\tcategory does not have enough questions to run for the game, then a random question from the rest \n"
        << "\tof the categories would be chosen at the difficulty level where there isn't a question from your \n"
        << "\tselected category available.\n\n"
        << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
        << "\tLIFELINES\n\n"
        << "\tAt any point, you may use up one (or more) of your three 'lifelines'. They are:\n"
        << "\t-- 50:50 - two of the three incorrect answers are removed. The removed answers are randomly selected.\n"
        << "\t-- Phone a friend - you may speak to someone on the phone for 30 seconds to discuss the question.\n"
        << "\t-- Ask the audience - the audience votes with their keypads on their choice of answer.\n\n"
        << "\tEach lifeline can ONLY be used ONCE during your entire game.\n\n"
        << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
        << "\tPRIZES\n\n"
        << "\tThe following lines show the number of the question and its value.\n"
        << "\t1 - $500\n"
        << "\t2 - $1 500\n"
        << "\t3 - $3 000\n"
        << "\t4 - $5 000 (first 'guarantee point')\n"
        << "\t5 - $10 000\n"
        << "\t6 - $15 000\n"
        << "\t7 - $25 000 (second 'guarantee point')\n"
        << "\t8 - $50 000\n"
        << "\t9 - $70 000\n"
        << "\t10 - $100 000\n\n";
}

void RulesShort()
{
    cout << "\n\tBefore we begin, let's make sure you are familiar with the manual rules.\n\n"
        << "\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"
        << "\tQUICK GAME RULES\n\n"
        << "\tYou must answer 10 multiple-choice questions correctly in order to win the big prize - $100 000.\n\n"
        << "\tThe questions are with increasing difficulty. You can quit at any time, earning the prize of the \n"
        << "\tprevious question. If you give a wrong answer, your earnings fall back to the last guarantee point\n"
        << "\tand you lose the game.\n\n"
        << "\tAt any point, you may use up one (or more) of your three 'lifelines'. They are:\n"
        << "\t-- 50:50  --            --  Phone a friend  --         -- Ask the audience --\n"
        << "\tEach lifeline can ONLY be used ONCE during your entire game.\n\n"
        << "\tThe following lines show the number of the question and the money you can win if you give right answer.\n\n"
        << "\t1 - $500                                 6 - $15 000\n"
        << "\t2 - $1 500                               7 - $25 000 (second 'guarantee point')\n"
        << "\t3 - $3 000                               8 - $50 000\n"
        << "\t4 - $5 000 (first 'guarantee point')     9 - $70 000 \n   "
        << "\t5 - $10 000                              10 - $100 000\n\n";
       
}