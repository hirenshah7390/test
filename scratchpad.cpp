
#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
void csvR()
{
	int exitCode;
	ifstream file;
	file.open("D:\\Desktop\\CongestedPathInput1.csv", ios::in);
	string value;
	if (file) {
		cout << "File exists";
	}
	while (file.good())
	{
		std::getline (file, value, ','); 
		cout << string(value, 1, value.length() - 2);
	}
}

int main() 
{
	
	csvR();
	getchar();
	return 0;
}