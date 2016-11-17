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

FloydWarshall::~FloydWarshall()
{

}

