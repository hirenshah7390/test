#pragma once
#include <stdio.h>
#include <conio.h>
#include <vector>
using namespace std;
class FloydWarshall
{

public:
	int n, src, dest;
	 int ** edgeWeights, ** flowMatrix, ** capacityMatrix, ** loadMatrix, ** delayMatrix;
	
	FloydWarshall();
	~FloydWarshall();
	int ** AdjacencyMatrix(int);
};

