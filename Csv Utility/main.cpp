#include <iostream>
#include <string>
#include "csvLoader.h"

int main(int argc, char** argv)
{
	std::cout << "Start of the project" << std::endl;

	if (argc != 2) {
		std::cerr << "ERROR INPUT" << std::endl;
		return 1;
	}

	std::string input_file_name = argv[1];

	std::ifstream input_file(input_file_name);

	CsvLoader * csvLoader = CsvLoader::getInstance();
	
	csvLoader->readCSV(input_file);
	

	return 0;
}