/*
SPPrediction class calculates delays in the system due to network traffic and implements methods for minimizing them.
*/

#include "SPPrediction.h"
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
#include <Windows.h>
#include <limits.h>
#define na 9999
#define NIL 8888
#define INF 6666

/*
9999 - na  (no edge)
8888 - NIL (predecessor matrix)
6666 - INF (gridlock)
*/

using namespace std;
FloydWarshall obj;

SPPrediction::SPPrediction()
{
}

SPPrediction::~SPPrediction()
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

//function to read the input file and load values n, a, b, E, F and C
void SPPrediction::ReadInputFile(string filename)
{
	ifstream file(filename);
	
	if (file.good()) {
		cout << "\nInput file found\n";
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
				obj.flowTraffic[i - 1][j - 1] = stoi(value);
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
						obj.edgeWeights = obj.floatMatrices(obj.n);
						for (int i = 0; i < obj.n; i++) {
							for (int j = 0; j < obj.n; j++) {
								if (i == j)
									obj.edgeWeights[i][j] = 0;
								else
									obj.edgeWeights[i][j] = na;
							}
						}

						obj.flowTraffic = obj.adjacencyMatrix(obj.n);
						obj.capacityMatrix = obj.adjacencyMatrix(obj.n);
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
		cout << "\nInput file not found\n";
	}
}

//function to calculate wall clock time
double SPPrediction::get_wall_time() {
	LARGE_INTEGER time, freq;
	if (!QueryPerformanceFrequency(&freq)) {
		return 0;
	}
	if (!QueryPerformanceCounter(&time)) {
		return 0;
	}
	return (double)time.QuadPart / freq.QuadPart;
}

//function to calculate CPU time
double SPPrediction::get_cpu_time() {
	FILETIME a, b, c, d;
	if (GetProcessTimes(GetCurrentProcess(), &a, &b, &c, &d) != 0) {
		return
			(double)(d.dwLowDateTime |
			((unsigned long long)d.dwHighDateTime << 32)) * 0.0000001;
	}
	else {
		return 0;
	}
}

//function to recompute edges
vector<vector<float>> SPPrediction::recomputeEdges(vector<vector<float>> actualEdgeDelay, vector<vector<int>> updatedFlowTraffic) {
	obj.edgeWeights = actualEdgeDelay;

	//Intialize a matrix with edge weights to apply Floyd-Warshall logic. 
	obj.actualAllPairsSP = obj.edgeWeights;

	//One way to track hops and hopcount: create a predecessor matrix to keep track of intermediate vertices in our path. Refer to CLRS Pg.697 "Predecessor matrix".
	obj.predecessorMatrix = obj.adjacencyMatrix(obj.n);

	//Initialize predecessorMatrix
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			if ((i == j) || (obj.edgeWeights[i][j] >= na))
				obj.predecessorMatrix[i][j] = NIL;
			else if ((i != j) && (obj.edgeWeights[i][j] < INF))
				obj.predecessorMatrix[i][j] = i;
		}
	}

	for (int k = 0; k < obj.n; k++) {
		//Predecessor matrix logic
		for (int i = 0; i < obj.n; i++) {
			for (int j = 0; j < obj.n; j++) {
				if (obj.actualAllPairsSP[i][j] > obj.actualAllPairsSP[i][k] + obj.actualAllPairsSP[k][j])
					obj.predecessorMatrix[i][j] = obj.predecessorMatrix[k][j];
				else if (obj.actualAllPairsSP[i][j] <= obj.actualAllPairsSP[i][k] + obj.actualAllPairsSP[k][j])
					obj.predecessorMatrix[i][j] = obj.predecessorMatrix[i][j];
			}
		}
		//Floyd-Warshall logic
		for (int i = 0; i < obj.n; i++) {
			for (int j = 0; j < obj.n; j++) {
				if (obj.actualAllPairsSP[i][j] > obj.actualAllPairsSP[i][k] + obj.actualAllPairsSP[k][j]) {
					obj.actualAllPairsSP[i][j] = obj.actualAllPairsSP[i][k] + obj.actualAllPairsSP[k][j];
				}
			}
		}
	}

	//Printing all pairs shortest path matrix
	cout << "\nAll pairs shortest paths using Floyd-Warshall algorithm is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.actualAllPairsSP[i][j] << "\t";
		cout << endl;
	}

	//Printing predecessor matrix
	cout << "\nPredecessor matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.predecessorMatrix[i][j] << "\t";
		cout << endl;
	}

	obj.actualPaths = obj.initializeActualSPMatrix(obj.n);

	//Load matrix initialization and definition
	obj.loadMatrix = updatedFlowTraffic;
	for (int i = 0; i < obj.n; i++)
		for (int j = 0; j < obj.n; j++) {
			if (obj.edgeWeights[i][j] >= INF)
				obj.loadMatrix[i][j] = na;
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
					//check if load is greater than capacity
					obj.loadMatrix[src][dest] += updatedFlowTraffic[i][j];
					if (obj.actualAllPairsSP[i][j] < obj.edgeWeights[i][j] && obj.edgeWeights[i][j] != na)
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
				cout << obj.actualPaths[i][j][k] + 1;
				cout << ",";
			}
			cout << "\t";
		}
		cout << endl;
	}

	//Hopcount matrix initialization, definition and printing
	obj.hopCountMatrix = obj.adjacencyMatrix(obj.n);
	cout << "\nHopcount matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			obj.hopCountMatrix[i][j] = (obj.actualPaths[i][j].size() - 1);
			cout << obj.hopCountMatrix[i][j] << "\t";
		}
		cout << endl;
	}

	//Printing load matrix
	cout << "\nLoad matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.loadMatrix[i][j] << "\t";
		cout << endl;
	}

	//print capacity matrix
	cout << "\nCapacity matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++)
			cout << obj.capacityMatrix[i][j] << "\t";
		cout << endl;
	}

	//Initialize, define and print actual edge delay matrix
	obj.actualEdgeDelay = obj.floatMatrices(obj.n);
	cout << "\nActual edge delay matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			if (obj.loadMatrix[i][j] <= obj.capacityMatrix[i][j]) {
				float num = obj.capacityMatrix[i][j] + 1;
				float den = obj.capacityMatrix[i][j] + 1 - obj.loadMatrix[i][j];
				obj.actualEdgeDelay[i][j] = (num / den) * (obj.edgeWeights[i][j]);
			}
			else if (obj.loadMatrix[i][j] == na)
				obj.actualEdgeDelay[i][j] = na;
			else if (obj.loadMatrix[i][j] > obj.capacityMatrix[i][j])
				obj.actualEdgeDelay[i][j] = INF;
			if (obj.actualEdgeDelay[i][j] == INF) 
				cout << "INF\t";
			else if (obj.actualEdgeDelay[i][j] >= na)
				cout << "na\t";
			else
				cout << obj.actualEdgeDelay[i][j] << "\t";
		}
		cout << endl;
	}

	//Initialize, define and print all pairs shortest paths (congested paths matrix) for total traffic loads on each edge
	obj.actualPathDelay = obj.floatMatrices(obj.n);
	obj.actualPathDelay = obj.actualEdgeDelay;

	for (int k = 0; k < obj.n; k++)
		for (int i = 0; i < obj.n; i++)
			for (int j = 0; j < obj.n; j++)
				if ((obj.actualEdgeDelay[i][j] >= 9999) || (obj.hopCountMatrix[i][j] > 1)) {
					obj.actualPathDelay[i][j] = 0;
					for (int k = 0; k < obj.hopCountMatrix[i][j]; k++) {
						if ((obj.actualEdgeDelay[obj.actualPaths[i][j][k]][obj.actualPaths[i][j][k + 1]]) < 9999)
							obj.actualPathDelay[i][j] += obj.actualEdgeDelay[obj.actualPaths[i][j][k]][obj.actualPaths[i][j][k + 1]];
						if (obj.actualPathDelay[i][j] > 6666)
							obj.actualPathDelay[i][j] = 6666;
					}
				}
	cout << "\nActual path delay matrix is \n";
	for (int i = 0; i < obj.n; i++) {
		for (int j = 0; j < obj.n; j++) {
			if (obj.actualPathDelay[i][j] == INF)
				cout << "INF\t";
			else if (obj.actualPathDelay[i][j] >= na)
				cout << "na\t";
			else 
				cout << obj.actualPathDelay[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\nShortest predicted path length from " << obj.src << " to " << obj.dest << " is ";
	if (obj.actualPathDelay[obj.src - 1][obj.dest - 1] == 6666)
		cout << "inf";
	else if (obj.actualPathDelay[obj.src - 1][obj.dest - 1] == 9999)
		cout << "na";
	else cout << obj.actualPathDelay[obj.src - 1][obj.dest - 1];

	cout << "\nShortest actual path length from " << obj.src << " to " << obj.dest << " is " << obj.actualAllPairsSP[obj.src - 1][obj.dest - 1];
	
	cout << "\nShortest predicted edge length from " << obj.src << " to " << obj.dest << " is ";
	if (obj.actualEdgeDelay[obj.src - 1][obj.dest - 1] == 6666)
		cout << "inf";
	else if (obj.actualEdgeDelay[obj.src - 1][obj.dest - 1] >= 9999)
		cout << "na";
	else cout << obj.actualEdgeDelay[obj.src - 1][obj.dest - 1];

	cout << "\nShortest actual edge length from " << obj.src << " to " << obj.dest << " is ";
	if (obj.actualEdgeDelay[obj.src - 1][obj.dest - 1] == 6666)
		cout << "inf";
	else if (obj.actualEdgeDelay[obj.src - 1][obj.dest - 1] >= 9999)
		cout << "na";
	else cout << obj.actualEdgeDelay[obj.src - 1][obj.dest - 1];
	
	cout << "\nHop-count of the path between " << obj.src << " to " << obj.dest << " is ";
	if (obj.hopCountMatrix[obj.src - 1][obj.dest - 1] < 0)
		cout << 0;
	else obj.hopCountMatrix[obj.src - 1][obj.dest - 1];
	
	cout << "\nVertices in shortest path from " << obj.src << " to " << obj.dest << " are ";
	
	for (int k = 0; k < obj.actualPaths[obj.src - 1][obj.dest - 1].size(); k++) {
		cout << obj.actualPaths[obj.src - 1][obj.dest - 1][k] + 1;
		cout << ",";
	}
	return obj.actualEdgeDelay;
}

int main()
{
	HANDLE hFind;
	WIN32_FIND_DATA data;
	SPPrediction parser;

	double wallClockTBegin = parser.get_wall_time();
	double CPUTimeBegin = parser.get_cpu_time();

	//Path to input file
	hFind = FindFirstFile("C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\Inputs2\\*.txt", &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			parser.ReadInputFile("C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\Inputs2\\" + string(data.cFileName));

			//allocate all s-t traffic, such that s and t are one hop away from each other, follwed by all s-t pairs that are two hops away, and so on
			obj.updatedFlowTraffic = obj.adjacencyMatrix(obj.n);

			//initialize a matrix for storing recomputing edge weights
			obj.recomputedEdgeDelay = obj.edgeWeights;
			for (int i = 0; i < obj.n; i++)
				for (int j = 0; j < obj.n; j++)
					obj.updatedFlowTraffic[i][j] = 0;

			//Allocate all s-t traffic to flow matrix, such that s and t are one hop away from each other, follwed by all s-t pairs that are two hops away, and so on
			for (int i = 1; i < obj.n; i++) {
				for (int j = 0; (j + i) < obj.n; j++) {
					obj.updatedFlowTraffic[j][j + i] = obj.flowTraffic[j][j + i];
					obj.updatedFlowTraffic[j + i][j] = obj.flowTraffic[j + i][j];
				}
				obj.actualEdgeDelay = parser.recomputeEdges(obj.recomputedEdgeDelay, obj.updatedFlowTraffic);				
			}
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	double wallClockTEnd = parser.get_wall_time();
	double CPUTimeEnd = parser.get_cpu_time();
	cout << endl;
	cout << "\nWall clock Time = " << wallClockTEnd - wallClockTBegin;
	cout << "\nCPU Time  = " << CPUTimeEnd - CPUTimeBegin << endl;
	getchar();
	return 0;
}