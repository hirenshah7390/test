#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>

FloydWarshall::FloydWarshall()
{

}


//This function creates an adjacency matrix of the size provided as input. 
vector<vector<int>> FloydWarshall::AdjacencyMatrix(int n)
{
	/*int **adj;
	adj = new int*[n];
	for (int i = 0; i < n; i++)
	{
		adj[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			adj[i][i] = 0;
		}
	}
	*/
	vector< vector<int> > adj(n, vector<int>(n, 9999));
	for (int i = 0; i < n; i++)
		adj[i][i] = 0;
	return adj;
	}


//Method to print all pairs shortest paths from source to destination
int FloydWarshall::printShortestPath(vector<vector<int>> predecessorMatrix, int i, int j)
{
	if (i == j) {
		cout << i;
		return i;
	}
	else if (predecessorMatrix[i][j] == 8888) {
		cout << 7777;
		return 7777;
	}
	else {
		printShortestPath(predecessorMatrix, i, predecessorMatrix[i][j]);
		cout << j;
		return j;
	}
}

FloydWarshall::~FloydWarshall()
{

}

