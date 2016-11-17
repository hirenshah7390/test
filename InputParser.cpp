#include "InputParser.h"
#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>

using namespace std;
FloydWarshall obj;
InputParser::InputParser()
{
}


InputParser::~InputParser()
{
}

//This function reads the file and saves the data in the matrices of EdgeWeight, FlowMatrix and CapacityMatrix.
void InputParser::ReadInputFile()
{
	ifstream file("C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\CongestedPathInput1.csv");
	obj.edgeWeights = obj.AdjacencyMatrix(6);
	obj.flowMatrix = obj.AdjacencyMatrix(6);
	obj.capacityMatrix = obj.AdjacencyMatrix(6);


	if (file.good()) {
		cout << "file exists";
		string value;
		string delimiter = ",";
		int i, j;
		size_t pos;
		string token;
		while (getline(file, value, '\n')) {
			pos = 0;
			if (value.find("E") != std::string::npos)
			{
				value = value.substr(3, value.length() - 1);
				while ((pos = value.find(delimiter)) != std::string::npos) {
					if (pos == 1)
					{
						i = stoi(value.substr(0, pos));
					}

					else if (pos == 2)
					{
						j = stoi(value.substr(0, pos));
					}
					value.erase(0, pos + delimiter.length());
				}
				obj.edgeWeights[i-1][j-1] = stoi(value);
			}

			else if (value.find("F") != std::string::npos)
			{
				value = value.substr(3, value.length() - 1);
				while ((pos = value.find(delimiter)) != std::string::npos) {
					if (pos == 1)
					{
						i = stoi(value.substr(0, pos));
					}

					else if (pos == 2)
					{
						j = stoi(value.substr(0, pos));
					}
					value.erase(0, pos + delimiter.length());
				}
				obj.flowMatrix[i-1][j-1] = stoi(value);
			}
			else if (value.find("C") != std::string::npos)
			{
				value = value.substr(3, value.length() - 1);
				while ((pos = value.find(delimiter)) != std::string::npos) {
					if (pos == 1)
					{
						i = stoi(value.substr(0, pos));
					}

					else if (pos == 2)
					{
						j = stoi(value.substr(0, pos));
					}
					value.erase(0, pos + delimiter.length());
				}
				obj.capacityMatrix[i-1][j-1] = stoi(value);
			}
			else
			{
				while ((pos = value.find(delimiter)) != std::string::npos) {
					if (pos == 1)
					{
						obj.n = stoi(value.substr(0, pos));
					}

					else if (pos == 2)
					{
						obj.src = stoi(value.substr(0, pos));
					}
					value.erase(0, pos + delimiter.length());
				}
				obj.dest = stoi(value);
			}

		}
	}
	else {
		cout << "file doesn't exist";
	}
}

int main()
{
	InputParser parser;
	parser.ReadInputFile();
	cout << "\nNumber of vertices are ";
	cout << obj.n;
	cout << "\n";

	cout << "\nEdge matrix is E \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.edgeWeights[i][j] << " ";
		cout << endl;
	}

	obj.allPairsShortestMatrix = obj.edgeWeights;
	for (int k = 0; k < obj.n; k++)
		for (int i = 0; i < obj.n; i++)
			for (int j = 0; j < obj.n; j++)
				if (obj.allPairsShortestMatrix[i][j]>obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j])
					obj.allPairsShortestMatrix[i][j] = obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j];

	cout << "\nAll pairs shortest paths for single car without traffic using Floyd-Warshall algorithm is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.allPairsShortestMatrix[i][j] << " ";
			cout << endl;
	}
	getchar();
	return 0;
}