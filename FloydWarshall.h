#pragma once
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;
class FloydWarshall
{
public:
	int n, k, src, dest;
	 vector<vector<int>> edgeWeights, flowMatrix, capacityMatrix, loadMatrix, delayMatrix, allPairsShortestMatrix, hopCountMatrix, predecessorMatrix;

	 vector<vector<string>> actualPathsString(int n), actualPathsStringMatrix, sLoadMatrix;

	 vector<vector<float>> floatMatrices(int n), actualEdgeDelayMatrix, actualPathDelayMatrix;

	 vector<vector<vector<int>>> actualShortestPathMatrix(int), actualPaths;
	 FloydWarshall();
	~FloydWarshall();
	vector<vector<int>> AdjacencyMatrix(int);
	int actualShortestPath(vector<vector<int>>, int, int, int, vector<vector<vector<int>>> &, vector<vector<int>> &);
};

