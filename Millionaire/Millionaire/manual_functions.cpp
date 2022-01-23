#include "manual_functions.h"
#include "hpfunctions.h"
#include <iostream>
#include <algorithm>
using namespace std;

// it works for only positive numbers, negative ones are never used nor needed
int ConvertStringToInt(string str)
{
	int number = 0;
	int multBy10 = 1;
	for (int i = str.size() - 1; i >= 0; i--)
	{
		if (str[i] < 48 || str[i] > 57)
		{
			return -1;
		}
		number += (str[i] - 48) * multBy10;
		multBy10 *= 10;
	}
	return number;
}

void stringToLower(string& s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
}

string returnStringToLower(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#else
	for (int i = 0; i <= 1000; i++)
	{
		cout << endl;
	}
#endif
}

void pressAnyKeyToContinueSimulation()
{
#ifdef _WIN32
	system("pause");
#elif __linux__
	system("read");
#else
	cout << "Press any key and then the 'Enter' key to continue . . .";
	string n;
	cin >> n;

#endif
}

void SwapStrings(string& a, string& b)
{
	string c = a;
	a = b;
	b = c;
}

void sortIntArr(int*& arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] < arr[j + 1])
			{
				SwapInt(arr[j], arr[j + 1]);
			}
		}
	}
}

void SwapInt(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

void GoBackToMain()
{
	clearScreen();
	Homepage();
}