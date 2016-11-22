#pragma once
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;
class InputParser
{
public:
	InputParser();
	~InputParser();
	void ReadInputFile();
	vector<vector<float>> recE(vector<vector<float>>);
};

