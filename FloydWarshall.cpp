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

void FloydWarshall::ReadInputFile(std::string filePath)
{
	ifstream file("C://Users//hhstm4//Source//Repos//CS5592Project//CS5592Project//CongestedPathInput1.csv");
	edgeWeights = AdjacencyMatrix(6);
	flowMatrix = AdjacencyMatrix(6);
	capacityMatrix = AdjacencyMatrix(6);


	if (file.good()) {
		cout << "file exists";
	}
	else {
		cout << "file doesn't exist";
	}

	string value;
	int i, j;
	while (getline(file, value, '\n')) {
		if (value.find("E") != string::npos)
		{
			
			cout << string(value);
			cout << "\n";
		}
	}
	
	
}



FloydWarshall::~FloydWarshall()
{

}
