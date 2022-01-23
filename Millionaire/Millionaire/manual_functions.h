#pragma once
#ifndef MANUAL_FUNCTIONS_H
#define MANUAL_FUNCTIONS_H
#include <iostream>

// function that converts given string to int, if possible
int ConvertStringToInt(std::string str);

// function that returns copy of the string in lowercase
std::string returnStringToLower(std::string s);

// function that converts the given string to lowercase
void stringToLower(std::string& s);

// function that pauses the work of the program
void pressAnyKeyToContinueSimulation();

// function that clears the console
void clearScreen();

// function that swaps the values of two given strings
void SwapStrings(std::string& a, std::string& b);

// function that sorts the given array to descending, using bubble sort type
void sortIntArr(int*& arr, int n);

// function that swaps the values of two given int elements
void SwapInt(int& a, int& b);

// function that calls clears the console and calls the main window
void GoBackToMain();

#endif