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
	//void ReadInputFile(string filename);
	void ReadInputFile();
	vector<vector<float>> recomputeEdges(vector<vector<float>>,vector<vector<int>>);
};

