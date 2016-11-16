#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
using namespace std;
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

//void FloydWarshall::ReadInputFile(string filePath)
//{
//	ifstream file(filePath); 
//	while (file.good())
//	{
//		getline(file, filePath, ','); 
//		cout << string(filePath, 1, filePath.length() - 2);
//	}
//}



FloydWarshall::~FloydWarshall()
{

}
