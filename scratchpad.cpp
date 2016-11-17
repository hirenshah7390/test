
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int csvR()
{
	
	std::ifstream file ("C:\\Users\\mom\\Google Drive\\fall 2016 semester\\design and analysis of algorithms\\my work\\my project\\CS5592Project\\CS5592Project\\CongestedPathInput1.csv");

	/*if (file.good()) {
		cout << "file exists";
	}
	else {
		cout << "file doesn't exist";
	}
	*/
	string value;


	string delimiter = ",";
	while (getline(file, value, '\n')) {
		if (value.find("E") != std::string::npos)
		{
			size_t pos = 0;
			string token;
			value = value.substr(3, value.length() - 1);
			while ((pos = value.find(delimiter)) != std::string::npos) {
				token = value.substr(0, pos);
				cout << token << endl;
				value.erase(0, pos + delimiter.length());
			}
			cout << value << endl;
			cout << "\n";
		}
	}
	return 0;
}
//int main() {
//	csvR();
//	getchar();
//	return 0;
//}