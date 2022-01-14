#pragma once
#ifndef MANUAL_FUNCTIONS_H
#define MANUAL_FUNCTIONS_H
#include <iostream>

int ConvertStringToInt(std::string str);

std::string returnStringToLower(std::string s);

void stringToLower(std::string& s);

void pressAnyKeyToContinueSimulation();

void clearScreen();

void SwapStrings(std::string& a, std::string& b);

#endif