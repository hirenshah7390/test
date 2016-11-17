#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int csvR()
{
	
	std::ifstream file ("D:\\Projects\\DAA project\\CS5592Project\\CongestedPathInput1.csv");	

	/*if (file.good()) {
		cout << "file exists";
	}
	else {
		cout << "file doesn't exist";
	}
	*/
	string value;	
	while (getline(file, value, '\n')) {
		if (value.find("E") != std::string::npos)
		{
			cout << string(value);
			cout << "\n";
		}
	}
	return 0;
}
int main() {
	csvR();
	getchar();
	return 0;
}