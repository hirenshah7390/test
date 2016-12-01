/*
SPPrediction class calculates delays in the system due to network traffic and implements methods for minimizing them.
*/
#pragma once
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;
class SPPrediction
{
public:
	SPPrediction();
	~SPPrediction();
	void ReadInputFile(string filename);
	vector<vector<float>> recomputeEdges(vector<vector<float>>, vector<vector<int>>);
	double get_wall_time(), get_cpu_time();
};