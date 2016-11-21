#include "InputParser.h"
#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <iterator>

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
	obj.n = 6;
	//"D:\\Projects\\DAA project\\CS5592Project\\CongestedPathInput1.csv"
	ifstream file("C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\CongestedPathInput1.csv");
	obj.edgeWeights = obj.AdjacencyMatrix(obj.n);
	obj.flowMatrix = obj.AdjacencyMatrix(obj.n);
	obj.capacityMatrix = obj.AdjacencyMatrix(obj.n);

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
	obj.n = 6;
	InputParser parser;
	parser.ReadInputFile();
	cout << "\nNumber of vertices are N = ";
	cout << obj.n;
	cout << "\n";

	cout << "\nEdge matrix is E \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.edgeWeights[i][j] << " ";
		cout << endl;
	}

	//Intialize a matrix with edge weights to apply Floyd-Warshall logic. 
	//We don't use edgeWeights matrix and overwrite it because we may need it for other approaches.
	obj.allPairsShortestMatrix = obj.edgeWeights;
	
	//One way to track hops and hopcount: create a temporary matrix to keep track of vertices in our path. Refer to CLRS Pg.697 "Predecessor matrix".
	obj.predecessorMatrix = obj.AdjacencyMatrix(obj.n);

	//Initialize predecessorMatrix
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			if ((i == j) || (obj.edgeWeights[i][j] == 9999))
				obj.predecessorMatrix[i][j] = 8888;
			else if ((i != j) && (obj.edgeWeights[i][j] < 9999))
				obj.predecessorMatrix[i][j] = i;
		}
	}

	//Print initial predecessor matrix
	cout << "\nInitial predecessor matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			cout << obj.predecessorMatrix[i][j] << " ";
		}
		cout << endl;
	}
	
	for (int k = 0; k < obj.n; k++) {
		//Predecessor matrix logic
		for (int i = 0; i < obj.n; i++) {
			for (int j = 0; j < obj.n; j++) {
				if (obj.allPairsShortestMatrix[i][j] > obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j])
					obj.predecessorMatrix[i][j] = obj.predecessorMatrix[k][j];
				else if (obj.allPairsShortestMatrix[i][j] <= obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j])
					obj.predecessorMatrix[i][j] = obj.predecessorMatrix[i][j];
			}
		}
		//Floyd-Warshall logic
		for (int i = 0; i < obj.n; i++) {
			for (int j = 0; j < obj.n; j++) {
				if (obj.allPairsShortestMatrix[i][j] > obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j]) {
					obj.allPairsShortestMatrix[i][j] = obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j];
				}
			}
		}
	}

	cout << "\nAll pairs shortest paths for single car without traffic using Floyd-Warshall algorithm is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.allPairsShortestMatrix[i][j] << " ";
			cout << endl;
	}

	//Printing predecessor matrix
	cout << "\nPredecessor matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.predecessorMatrix[i][j] << " ";
		cout << endl;
	}

	obj.actualPaths = obj.actualShortestPathMatrix(obj.n);
    
	//Load matrix initialization and definition
	obj.loadMatrix = obj.AdjacencyMatrix(obj.n);
	for (int i = 0; i < obj.n; i++)
		for (int j = 0; j < obj.n; j++) {
			if (obj.edgeWeights[i][j] == 9999)
				obj.loadMatrix[i][j] = 9999;
			else
				obj.loadMatrix[i][j] = 0;
		}

	//calling actual shortest path function
	for (int i = 0; i < obj.n; i++)
		for (int j = 0; j < obj.n; j++) {
			int duplicatej = j;
			obj.actualShortestPath(obj.predecessorMatrix, i, j, duplicatej, obj.actualPaths, obj.loadMatrix);
		}
	
	//Printing actual all pairs shortest paths matrix
	cout << "\nActual all pairs shortest paths matrix is\n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			for (int k = 0; k < obj.actualPaths[i][j].size(); k++) {
				cout << obj.actualPaths[i][j][k] + 1;
			}
			cout << " ";
		}
		cout << endl;
	}

	//Hopcount matrix initialization, definition and printing
	obj.hopCountMatrix = obj.AdjacencyMatrix(obj.n);
	cout << "\nHopcount matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			obj.hopCountMatrix[i][j] = (obj.actualPaths[i][j].size() - 1);
			cout << obj.hopCountMatrix[i][j] << " ";
		}
		cout << endl;
	}



	//for (int i = 0; i < obj.n; i++) {
	//	for (int j = 0; j < obj.n; j++) {
	//		for (int k = 0; k < obj.hopCountMatrix[i][j]; k++) {
	//			if ((obj.actualPaths[i][j][k] == i) && (obj.actualPaths[i][j][k + 1] == j))
	//				obj.loadMatrix[i][j] += obj.flowMatrix[i][(obj.actualPaths[i][j][obj.hopCountMatrix[i][j]])];
	//		}
	//		cout << obj.loadMatrix[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	/*for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			for (int k = 0; k < obj.hopCountMatrix[i][j]; k++) {
				if ((obj.actualPaths[i][j][k] == i) && k != obj.hopCountMatrix[i][j])
					if (obj.actualPaths[i][j][k + 1] == j)
							obj.loadMatrix[i][j] += obj.flowMatrix[i][(obj.actualPaths[i][j][obj.hopCountMatrix[i][j]])];
					}
			cout << obj.loadMatrix[i][j] << " ";
		}
		cout << endl;
	}*/
	
	//Printing load matrix
	cout << "\nLoad matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.loadMatrix[i][j] << " ";
		cout << endl;
	}

	//converting actual path matrix into string matrix
	/*obj.actualPathsStringMatrix = obj.actualPathsString(obj.n);
	obj.sLoadMatrix = obj.AdjacencyMatrix(obj.n);
	cout << "\String actual path matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			std::stringstream result;
			std::copy(obj.actualPaths[i][j].begin(), obj.actualPaths[i][j].end(), std::ostream_iterator<int>(result, ","));
			obj.actualPathsStringMatrix[i][j] = result.str();
			if (result.str().find(to_string(i) + "," + to_string(j)))
				obj.sLoadMatrix[i][j] += obj.flowMatrix[i][(obj.actualPaths[i][j][obj.hopCountMatrix[i][j]])];
			cout << obj.actualPathsStringMatrix[i][j] << " ";
		}
		cout << endl;
	}*/

	getchar();
	return 0;
}

