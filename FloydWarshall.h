/*
FloydWarshall class retrieves intermediate vertices in a shortest path for all shortest path pairs computed using Floyd-Warshall algorithm.
*/
#pragma once
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;
class FloydWarshall
{
public:
	int n, k, src, dest;
	 vector<vector<int>>  flowTraffic, updatedFlowTraffic, capacityMatrix, loadMatrix, hopCountMatrix, predecessorMatrix;
	 vector<vector<float>> floatMatrices(int n), edgeWeights, actualEdgeDelay, actualPathDelay, actualAllPairsSP, recomputedEdgeDelay;
	 vector<vector<vector<int>>> initializeActualSPMatrix(int), actualPaths;
	 FloydWarshall();
	~FloydWarshall();
	vector<vector<int>> adjacencyMatrix(int);
	int actualShortestPath(vector<vector<int>>, int, int, int, vector<vector<vector<int>>> &, vector<vector<int>> &);
};