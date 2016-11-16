#include "FloydWarshall.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int csvR()
{
	
	std::ifstream file ("C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\CongestedPathInput1.csv");
	if (file.good()) {
		cout << "file exists";
	}
	else {
		cout << "file doesn't exist";
	}
	
	string value;
	cout<<"yepppppppppppppppppp";
	while (getline(file, value, ',')) {
		cout << string(value, 1, value.length() - 2);
	}
	return 0;
}
int main() {
	csvR();
	getchar();
	return 0;
}