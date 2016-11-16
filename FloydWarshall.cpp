#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
FloydWarshall::FloydWarshall()
{

}

//This function creates an adjacency matrix of the size provided as input. 
int ** FloydWarshall::AdjacencyMatrix(int n)
{
	int **adj;
	adj = new int*[n];
	for (int i = 0; i < n; i++)
	{
		adj[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			adj[i][j] = 0;
		}
	}
	return adj;
}



FloydWarshall::~FloydWarshall()
{

}
