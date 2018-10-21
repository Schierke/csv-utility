#include "csvLoader.h"

// standard library:
#include <sstream>

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

void CsvRow::getData(std::string data)
{
	std::stringstream tempRowData(data);
	std::string tempData;
	while (std::getline(tempRowData, tempData, ';')) {
		m_data.push_back(tempData);
	}
}

void CsvRow::printData()
{
	for (auto i = m_data.begin(); i != m_data.end(); i++) {
		std::cout << *i << ";" << std::endl;
	}
	std::cout << std::endl;
}
