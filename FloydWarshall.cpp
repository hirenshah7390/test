/*
FloydWarshall class retrieves intermediate vertices in a shortest path for all shortest path pairs computed using Floyd-Warshall algorithm.
*/

#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>

vector<vector<float>> FloydWarshall::floatMatrices(int n)
{
	vector<vector<float>> floatMatrix(n, vector<float>(n, 0.0));
	return floatMatrix;
}

vector<vector<vector<int>>> FloydWarshall::initializeActualSPMatrix(int n)
{
	vector<vector<vector<int>>> initializeActualSPM(n, vector<vector<int>>(n, vector<int>(0,1)));
	return initializeActualSPM;
}

FloydWarshall::FloydWarshall()
{
}

//Function to create an adjacency matrix of the size provided as input n. 
vector<vector<int>> FloydWarshall::adjacencyMatrix(int n)
{
	vector< vector<int> > adj(n, vector<int>(n, 9999));
	for (int i = 0; i < n; i++)
		adj[i][i] = 0;
	return adj;
}

//Method to calculate actual all pairs shortest paths from source to destination
int FloydWarshall::actualShortestPath(vector<vector<int>> predecessorMatrix, int i, int j, int duplicatej, vector<vector<vector<int>>> &actualPathsCal, vector<vector<int>> &loadMatrix)
{
	if (i == j) {
		//Adding the source and destintion vertices to the shortest path.
		actualPathsCal[i][duplicatej].push_back(i);
		return i;	
	}
	//Returning NA if there is no direct route present between the source and destination.
	else if (predecessorMatrix[i][j] == 8888) {
		return 7777;
	}
	else {
		//Recursively calling the shortest path to add the intermediate vertices along the shortest path.
		actualShortestPath(predecessorMatrix, i, predecessorMatrix[i][j], duplicatej, actualPathsCal, loadMatrix);
		actualPathsCal[i][duplicatej].push_back(j);
		return j;
	}
}

FloydWarshall::~FloydWarshall()
{

}