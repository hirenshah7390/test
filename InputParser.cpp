#include "InputParser.h"
#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <iterator>
#include <windows.h>
#include <tchar.h> 
#include <strsafe.h>
#include <string>
#pragma comment(lib, "User32.lib")
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>


/*
shorthand codes:
9999 - na (no edge)
8888 - NIL (predecessor matrix)
7777 - NA (no direct route)
6666 - infinity (gridlock)
*/

using namespace std;
FloydWarshall obj;

InputParser::InputParser()
{
}

InputParser::~InputParser()
{
}

static inline std::string &ltrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}

//This function reads the file and saves the data in the matrices of EdgeWeight, FlowMatrix and CapacityMatrix.
void InputParser::ReadInputFile(string filename)
{
	obj.n = 6;
	//D:\\Projects\\DAA project\\CS5592Project\\CongestedPathInput1.csv
	//C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\CongestedPathInput1.csv
	ifstream file(filename);

	//obj.edgeWeights = obj.floatMatrices(obj.n);

	/*for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			if (i == j)
				obj.edgeWeights[i][j] = 0;
			else
				obj.edgeWeights[i][j] = 9999;
		}
	}

	obj.flowMatrix = obj.AdjacencyMatrix(obj.n);
	obj.capacityMatrix = obj.AdjacencyMatrix(obj.n);*/

	if (file.good()) {
		cout << "\nfile exists\n";
		string value;
		string delimiter = ",";
		int i, j;
		size_t pos;
		int position = 0;
		string token;
		while (getline(file, value, '\n')) {
			pos = 0;
			value = trim(value);
			if (value == "")
				continue;
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
				obj.edgeWeights[i - 1][j - 1] = stoi(value);
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
				obj.flowMatrix[i - 1][j - 1] = stoi(value);
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
				obj.capacityMatrix[i - 1][j - 1] = stoi(value);
			}
			else
			{
				while ((pos = value.find(delimiter)) != std::string::npos) {					
					if (position == 0)
					{
						obj.n = stoi(value.substr(0, pos));

						//Shifted initialization right after new value of obj.n
						obj.edgeWeights = obj.floatMatrices(obj.n);
						for (int i = 0; i < obj.n; i++) {
							for (int j = 0; j < obj.n; j++) {
								if (i == j)
									obj.edgeWeights[i][j] = 0;
								else
									obj.edgeWeights[i][j] = 9999;
							}
						}

						obj.flowMatrix = obj.AdjacencyMatrix(obj.n);
						obj.capacityMatrix = obj.AdjacencyMatrix(obj.n);

						position = position + 1;

					}

					else if (position == 1)
					{
						obj.src = stoi(value.substr(0, pos));
						position = position + 1;
					}
					value.erase(0, pos + delimiter.length());
				}
				obj.dest = stoi(value);
			}

		}
	}
	else {
		cout << "\nfile doesn't exist\n";
	}

}

//vector<vector<float>> InputParser::recomputeEdges(vector<vector<float>> actualEdgeDelayMatrix, vector<vector<int>> tempFlowMatrix) {
//	obj.n = 6;
//	InputParser parser;
//	parser.ReadInputFile();
//	cout << "\n " << "*********************************************" << "Recomputing weights" << "************" ;
//	cout << "\nEdge matrix is E \n";
//
//	obj.edgeWeights = actualEdgeDelayMatrix;
//
//	//Intialize a matrix with edge weights to apply Floyd-Warshall logic. 
//	//We don't use edgeWeights matrix and overwrite it because we may need it for other approaches.
//	obj.allPairsShortestMatrix = obj.edgeWeights;
//
//	//One way to track hops and hopcount: create a temporary matrix to keep track of vertices in our path. Refer to CLRS Pg.697 "Predecessor matrix".
//	obj.predecessorMatrix = obj.AdjacencyMatrix(obj.n);
//
//	//Initialize predecessorMatrix
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++) {
//			if ((i == j) || (obj.edgeWeights[i][j] == 9999))
//				obj.predecessorMatrix[i][j] = 8888;
//			else if ((i != j) && (obj.edgeWeights[i][j] < 9999))
//				obj.predecessorMatrix[i][j] = i;
//		}
//	}
//
//	for (int k = 0; k < obj.n; k++) {
//		//Predecessor matrix logic
//		for (int i = 0; i < obj.n; i++) {
//			for (int j = 0; j < obj.n; j++) {
//				if (obj.allPairsShortestMatrix[i][j] > obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j])
//					obj.predecessorMatrix[i][j] = obj.predecessorMatrix[k][j];
//				else if (obj.allPairsShortestMatrix[i][j] <= obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j])
//					obj.predecessorMatrix[i][j] = obj.predecessorMatrix[i][j];
//			}
//		}
//		//Floyd-Warshall logic
//		for (int i = 0; i < obj.n; i++) {
//			for (int j = 0; j < obj.n; j++) {
//				if (obj.allPairsShortestMatrix[i][j] > obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j]) {
//					obj.allPairsShortestMatrix[i][j] = obj.allPairsShortestMatrix[i][k] + obj.allPairsShortestMatrix[k][j];
//				}
//			}
//		}
//
//
//	}
//
//	cout << "\nAll pairs shortest paths for single car without traffic using Floyd-Warshall algorithm is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++)
//			cout << obj.allPairsShortestMatrix[i][j] << " ";
//		cout << endl;
//	}
//
//	//Printing predecessor matrix
//	cout << "\nPredecessor matrix is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++)
//			cout << obj.predecessorMatrix[i][j] << " ";
//		cout << endl;
//	}
//
//	obj.actualPaths = obj.actualShortestPathMatrix(obj.n);
//
//	//Load matrix initialization and definition
//	obj.loadMatrix = tempFlowMatrix;
//	for (int i = 0; i < obj.n; i++)
//		for (int j = 0; j < obj.n; j++) {
//			if (obj.edgeWeights[i][j] == 9999)
//				obj.loadMatrix[i][j] = 9999;
//			else
//				obj.loadMatrix[i][i] = 0;
//		}
//
//
//	//calling actual shortest path function
//	for (int i = 0; i < obj.n; i++)
//		for (int j = 0; j < obj.n; j++) {
//			int duplicatej = j;
//			obj.actualShortestPath(obj.predecessorMatrix, i, j, duplicatej, obj.actualPaths, obj.loadMatrix);
//			if (obj.actualPaths[i][j].size() > 2)
//			{
//				//This code helps in building the load matrix for the common edges in the shortest paths. Dynamic programming.
//				for (int k = 0; k < obj.actualPaths[i][j].size() - 1; k++)
//				{
//					int src = obj.actualPaths[i][j][k];
//					int dest = obj.actualPaths[i][j][k + 1];
//					obj.loadMatrix[src][dest] += tempFlowMatrix[i][j];
//					if (obj.allPairsShortestMatrix[i][j] < obj.edgeWeights[i][j] && obj.edgeWeights[i][j] != 9999)
//					{
//						obj.loadMatrix[i][j] = 0;
//					}
//
//				}
//			}
//		}
//
//	//Printing actual all pairs shortest paths matrix
//	cout << "\nActual all pairs shortest paths matrix is\n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++) {
//			for (int k = 0; k < obj.actualPaths[i][j].size(); k++) {
//				cout << obj.actualPaths[i][j][k] + 1;
//				cout << ",";
//			}
//			cout << "\t";
//		}
//		cout << endl;
//	}
//
//	//Hopcount matrix initialization, definition and printing
//	obj.hopCountMatrix = obj.AdjacencyMatrix(obj.n);
//	cout << "\nHopcount matrix is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++) {
//			obj.hopCountMatrix[i][j] = (obj.actualPaths[i][j].size() - 1);
//			cout << obj.hopCountMatrix[i][j] << " ";
//		}
//		cout << endl;
//	}
//
//	//Printing load matrix
//	cout << "\nLoad matrix is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++)
//			cout << obj.loadMatrix[i][j] << " ";
//		cout << endl;
//	}
//
//	//print capacity matrix
//	cout << "\nCapacity matrix is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++)
//			cout << obj.capacityMatrix[i][j] << " ";
//		cout << endl;
//	}
//
//	//Initialize, define and print actual edge delay matrix
//	obj.actualEdgeDelayMatrix = obj.floatMatrices(obj.n);
//	cout << "\nActual edge delay matrix is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++) {
//			float num = obj.capacityMatrix[i][j] + 1;
//			float den = obj.capacityMatrix[i][j] + 1 - obj.loadMatrix[i][j];
//			obj.actualEdgeDelayMatrix[i][j] = (num / den) * (obj.edgeWeights[i][j]);
//			cout << obj.actualEdgeDelayMatrix[i][j] << "\t  ";
//		}
//		cout << endl;
//	}
//
//	//Initialize, define and print all pairs shortest paths (congested paths matrix) for total traffic loads on each edge
//	obj.actualPathDelayMatrix = obj.floatMatrices(obj.n);
//	obj.actualPathDelayMatrix = obj.actualEdgeDelayMatrix;
//
//
//	for (int k = 0; k < obj.n; k++)
//		for (int i = 0; i < obj.n; i++)
//			for (int j = 0; j < obj.n; j++)
//				if ((obj.actualEdgeDelayMatrix[i][j] >= 9999) || (obj.hopCountMatrix[i][j] > 1)) {
//					obj.actualPathDelayMatrix[i][j] = 0;
//					for (int k = 0; k < obj.hopCountMatrix[i][j]; k++)
//						if ((obj.actualEdgeDelayMatrix[obj.actualPaths[i][j][k]][obj.actualPaths[i][j][k + 1]]) < 9999)
//							obj.actualPathDelayMatrix[i][j] += obj.actualEdgeDelayMatrix[obj.actualPaths[i][j][k]][obj.actualPaths[i][j][k + 1]];
//				}
//
//	cout << "\nRecomputed Actual path delay matrix is \n";
//	for (int i = 0; i < obj.n; i++) {
//		for (int j = 0; j < obj.n; j++)
//			cout << obj.actualPathDelayMatrix[i][j] << "\t";
//		cout << endl;
//	}
//	return actualEdgeDelayMatrix;
//}

int main()
{
	obj.n = 6;
	HANDLE hFind;
	WIN32_FIND_DATA data;
	InputParser parser;


	hFind = FindFirstFile("C:\\Users\\hhstm4\\Source\\Repos\\CS5592Project\\CS5592Project\\Inputs\\*.txt", &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			cout << "\nThis is the O/P for fileName = ";
			cout << data.cFileName;
			cout << "\n";

			parser.ReadInputFile("C:\\Users\\hhstm4\\Source\\Repos\\CS5592Project\\CS5592Project\\Inputs\\" + string(data.cFileName));
			cout << "\nShorthand codes are as follows:\n" << "9999 : na (no edge)\n" << "8888 : NIL\n" << "7777 : NA (no direct route)\n" << "6666 : Infinity (gridlock)\n";
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
			obj.loadMatrix = obj.flowMatrix;
			for (int i = 0; i < obj.n; i++)
				for (int j = 0; j < obj.n; j++) {
					if (obj.edgeWeights[i][j] == 9999)
						obj.loadMatrix[i][j] = 9999;
					else
						obj.loadMatrix[i][i] = 0;
				}


			//calling actual shortest path function
			for (int i = 0; i < obj.n; i++)
				for (int j = 0; j < obj.n; j++) {
					int duplicatej = j;
					obj.actualShortestPath(obj.predecessorMatrix, i, j, duplicatej, obj.actualPaths, obj.loadMatrix);
					if (obj.actualPaths[i][j].size() > 2)
					{
						//This code helps in building the load matrix for the common edges in the shortest paths. Dynamic programming.
						for (int k = 0; k < obj.actualPaths[i][j].size() - 1; k++)
						{
							int src = obj.actualPaths[i][j][k];
							int dest = obj.actualPaths[i][j][k + 1];
							obj.loadMatrix[src][dest] += obj.flowMatrix[i][j];
							if (obj.allPairsShortestMatrix[i][j] < obj.edgeWeights[i][j] && obj.edgeWeights[i][j] != 9999)
							{
								obj.loadMatrix[i][j] = 0;
							}

						}
					}
				}

			//Printing actual all pairs shortest paths matrix
			cout << "\nActual all pairs shortest paths matrix is\n";
			for (int i = 0; i < obj.n; i++) {
				for (int j = 0; j < obj.n; j++) {
					for (int k = 0; k < obj.actualPaths[i][j].size(); k++) {
						cout << obj.actualPaths[i][j][k] + 1 << ",";
					}
					cout << "\t";
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

			//Printing load matrix
			cout << "\nLoad matrix is \n";
			for (int i = 0; i < obj.n; i++) {
				for (int j = 0; j < obj.n; j++)
					cout << obj.loadMatrix[i][j] << " ";
				cout << endl;
			}

			//print capacity matrix
			cout << "\nCapacity matrix is \n";
			for (int i = 0; i < obj.n; i++) {
				for (int j = 0; j < obj.n; j++)
					cout << obj.capacityMatrix[i][j] << " ";
				cout << endl;
			}

			//Initialize, define and print actual edge delay matrix
			obj.actualEdgeDelayMatrix = obj.floatMatrices(obj.n);
			cout << "\nActual edge delay matrix is \n";
			for (int i = 0; i < obj.n; i++) {
				for (int j = 0; j < obj.n; j++) {
					float num = obj.capacityMatrix[i][j] + 1;
					float den = obj.capacityMatrix[i][j] + 1 - obj.loadMatrix[i][j];
					obj.actualEdgeDelayMatrix[i][j] = (num / den) * (obj.edgeWeights[i][j]);
					if (obj.actualEdgeDelayMatrix[i][j] < 0)
						obj.actualEdgeDelayMatrix[i][j] = 6666;
					if (obj.actualEdgeDelayMatrix[i][j] >= 9999)
						obj.actualEdgeDelayMatrix[i][j] = 9999;
					cout << obj.actualEdgeDelayMatrix[i][j] << "\t  ";
				}
				cout << endl;
			}

			//Initialize, define and print all pairs shortest paths (congested paths matrix) for total traffic loads on each edge
			obj.actualPathDelayMatrix = obj.floatMatrices(obj.n);
			obj.actualPathDelayMatrix = obj.actualEdgeDelayMatrix;

			for (int k = 0; k < obj.n; k++)
				for (int i = 0; i < obj.n; i++)
					for (int j = 0; j < obj.n; j++)
						if ((obj.actualEdgeDelayMatrix[i][j] >= 9999) || (obj.hopCountMatrix[i][j] > 1)) {
							obj.actualPathDelayMatrix[i][j] = 0;
							for (int k = 0; k < obj.hopCountMatrix[i][j]; k++) {
								if ((obj.actualEdgeDelayMatrix[obj.actualPaths[i][j][k]][obj.actualPaths[i][j][k + 1]]) < 9999)
									obj.actualPathDelayMatrix[i][j] += obj.actualEdgeDelayMatrix[obj.actualPaths[i][j][k]][obj.actualPaths[i][j][k + 1]];
								if (obj.actualPathDelayMatrix[i][j] > 6666)
									obj.actualPathDelayMatrix[i][j] = 6666;

							}
						}

			cout << "\nActual path delay matrix is \n";
			for (int i = 0; i < obj.n; i++) {
				for (int j = 0; j < obj.n; j++)
					cout << obj.actualPathDelayMatrix[i][j] << "\t";
				cout << endl;
			}

			//calling function for recomputing edges
			//allocate one s-t pair at one time
			//initialize a temporary matrix for incrementing flow one s-t pair at one time
			//obj.tempFlowMatrix = obj.AdjacencyMatrix(obj.n);
			////initialize a matrix for storing recomputing edge weights
			//obj.recomputedEdgeDelay = obj.edgeWeights;
			//for (int i = 0; i < obj.n; i++)
			//	for (int j = 0; j < obj.n; j++) {
			//		obj.tempFlowMatrix[i][j] = 0;
			//	}
			//
			//
			//for (int i = 0; i < obj.n; i++) 
			//	for (int j = 0; j < obj.n; j++) {
			//		obj.tempFlowMatrix[i][j] = obj.flowMatrix[i][j];
			//		obj.recomputedEdgeDelay = parser.recomputeEdges(obj.recomputedEdgeDelay, obj.tempFlowMatrix);
			//		cout << "\nRecomputed edge delay is\n";
			//		for (int k = 0; k < obj.n; k++) {
			//			for (int l = 0; l < obj.n; l++)
			//				cout << obj.recomputedEdgeDelay[k][l] << "\t";
			//			cout << endl;
			//		}
			//	}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}

	getchar();
	return 0;
}