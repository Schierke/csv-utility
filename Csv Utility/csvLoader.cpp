#include "csvLoader.h"

// stl:
#include <sstream>
#include <numeric>
#include <algorithm>

// boost
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

CsvLoader * CsvLoader::instance = 0;

CsvLoader* CsvLoader::getInstance()
{
	if (instance == 0)
	{
		instance = new CsvLoader();
	}

	return instance;
}

CsvLoader::CsvLoader()
{

}

void CsvLoader::readCSV(std::ifstream& str)
{
	std::string row;
	while (!str.eof())
	{
		std::getline(str, row, '\n');

		if (str.bad() || str.fail()) {
			break;
		}

		// saving the row into class csvRow:
		CsvRow * temporaryRow = new CsvRow();
		temporaryRow->getData(row);
		allRows.push_back(*temporaryRow);
	}

	// Debugging:
	for (auto i = allRows.begin(); i != allRows.end(); i++) {
		i->printData();
	}
}

void CsvLoader::processingMethod(const std::string & processingMethod, const std::string & parameter)
{

	// getting parameter
	Config::EnumParser<Config::METHOD> parse;
	Config::METHOD usingMethod = parse.parseSomeEnum(processingMethod);
	int indexRowSorting = boost::lexical_cast<int>(parameter);

	switch (usingMethod)
	{
	case Config::SORTING_BY_ROW:
		sortingByRow(indexRowSorting);
		break;
	case Config::SORTING_BY_NUMBER:
		break;
	default:
		break;
	}



}

void CsvLoader::sortingByRow(int indexRowSorting)
{
	// sorting alphabetically:
	std::vector<int> index;
	std::iota(index.begin(), index.end(), 0);

}

void CsvLoader::sortingByNumber()
{
}

void CsvRow::getData(std::string data)
{
	std::stringstream tempRowData(data);
	std::string tempData;
	while (std::getline(tempRowData, tempData, ';')) {
		m_data.push_back(tempData);
	}
}

std::string CsvRow::getRowData(int index)
{
	if (index > m_data.size()) {
		std::cerr << "ERROR INPUT: OUT OF BOUND ROW DATA" << std::endl;
		return "-- OUT OF BOUND --"; // TODO: use boost::optional
	}
	
	return m_data[index];
}

void CsvRow::printData()
{
	for (auto i = m_data.begin(); i != m_data.end(); i++) {
		std::cout << *i << ";" << std::endl;
	}
	std::cout << std::endl;
}
