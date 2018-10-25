#include "csvLoader.h"
#include "config.h"

// stl
#include <iostream>
#include <string>
#include <vector>
#include <map>


//boost
#include <boost/lexical_cast.hpp>


int main(int argc, char** argv)
{
	std::cout << "Start of the project" << std::endl;

	if (argc < 3) {
		std::cerr << "ERROR INPUT" << std::endl;
		return 1;
	}

	std::string input_file_name = argv[1];

	std::string processingMethod = argv[2];

	std::string parameter = argv[3];

	std::ifstream input_file(input_file_name);

	CsvLoader * csvLoader = CsvLoader::getInstance();
	
	csvLoader->readCSV(input_file);
	
	// processing by processingMethod:

	return 0;
}