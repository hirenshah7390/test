#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int csvR()
{
	std::ifstream file ("CongestedPathInput1.csv");
	string value;
	while (file.good())
	{
		std::getline (file, value, ','); 
		cout << string(value, 1, value.length() - 2); 
	}
	return 0;
}