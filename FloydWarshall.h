#pragma once
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;
class FloydWarshall
{

public:
	int n, src, dest;
	 vector<vector<int>> edgeWeights, flowMatrix, capacityMatrix, loadMatrix, delayMatrix, allPairsShortestMatrix;
	
	FloydWarshall();
	~FloydWarshall();
	vector<vector<int>> AdjacencyMatrix(int);
};

