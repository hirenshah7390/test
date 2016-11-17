#pragma once
#include <stdio.h>
#include <conio.h>
using namespace std;
class FloydWarshall
{

public:
	int n, src, dest;
	int ** edgeWeights, ** flowMatrix, ** capacityMatrix, ** loadMatrix, ** delayMatrix;
	FloydWarshall();
	~FloydWarshall();
	int ** AdjacencyMatrix(int);
	void ReadInputFile(std::string);
};

