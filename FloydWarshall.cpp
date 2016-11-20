#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
int n = 6;

vector<vector<vector<int>>> FloydWarshall::actualShortestPathMatrix(int n)
{
	vector<vector<vector<int>>> aspm(n, vector<vector<int>>(n, vector<int>(0,1)));
	return aspm;
}

FloydWarshall::FloydWarshall()
{
}

//This function creates an adjacency matrix of the size provided as input. 
vector<vector<int>> FloydWarshall::AdjacencyMatrix(int n)
{
	vector< vector<int> > adj(n, vector<int>(n, 9999));
	for (int i = 0; i < n; i++)
		adj[i][i] = 0;
	return adj;
}

//Method to calculate actual all pairs shortest paths from source to destination
int FloydWarshall::actualShortestPath(vector<vector<int>> predecessorMatrix, int i, int j, int duplicatej, vector<vector<vector<int>>> &actualPathsCal)
{
	if (i == j) {
		actualPathsCal[i][duplicatej].push_back(i);
		return i;	
	}
	else if (predecessorMatrix[i][j] == 8888) {
		return 7777;
	}
	else {
		actualShortestPath(predecessorMatrix, i, predecessorMatrix[i][j], duplicatej, actualPathsCal);
		actualPathsCal[i][duplicatej].push_back(j);
		return j;
	}
}

FloydWarshall::~FloydWarshall()
{

}

