#pragma once
class FloydWarshall
{

public:
	int n, src, dest;
	int ** edgeWeights, flowMatrix, capacityMatrix, loadMatrix, delayMatrix;
	FloydWarshall();
	int ** AdjacencyMatrix(int);
	~FloydWarshall();
};

