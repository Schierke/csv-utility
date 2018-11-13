#include "csvLoader.h"
#include "config.h"

// stl
#include <iostream>
#include <string>
#include <vector>
#include <map>


//boost
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

namespace bt_option = boost::program_options;

int main(int argc, char** argv)
{
	std::cout << "Start of the project" << std::endl;

	bt_option::options_description opt("Allowed options");

	opt.add_options()
		("help", "Help message")
		("input_file", bt_option::value<std::string>()->default_value("test.csv"), "set the input csv file name")
		("process_method", bt_option::value<std::string>()->default_value("SORTING_BY_ROW"), "set the processing method you want for input csv")
		("process_parameter", bt_option::value<std::string>()->default_value("2"), "the parameter of processing method. 2 methods: SORTING_BY_ROW and SORTING_BY_NUMBER")
		("process_order", bt_option::value<std::string>()->default_value("ASCENDING"), "the order of sorted csv: ASCENDING or DESCENDING")
		("output_file", bt_option::value<std::string>()->default_value("output.csv"),"result file")
		;
	bt_option::variables_map vm;

	bt_option::store(bt_option::parse_command_line(argc, argv, opt), vm);

	bt_option::notify(vm);

	if (vm.count("help")) {
		std::cout << opt << "\n";
		return 1;
	}

	// input file
	std::string input_file_name = vm["input_file"].as<std::string>();

	std::string processingMethod = vm["process_method"].as<std::string>();

	std::string parameter = vm["process_parameter"].as<std::string>();

	std::string process_order = vm["process_order"].as<std::string>();

	std::string output_file_name = vm["output_file"].as<std::string>();

	for (auto i : vm)
	{
		std::cout << i.second.as<std::string>() << std::endl;
	}

	std::ifstream input_file(input_file_name); 

	std::ofstream output_file(output_file_name);

	CsvLoader * csvLoader = CsvLoader::getInstance();
	
	csvLoader->readCSV(input_file);
	
	// processing by processingMethod:
	csvLoader->processingMethod(processingMethod, parameter);

	// set the result to File:
	csvLoader->writeCSV(output_file);


	return 0;
}