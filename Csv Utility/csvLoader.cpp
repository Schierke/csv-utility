#include "csvLoader.h"

// stl:
#include <sstream>
#include <numeric>
#include <algorithm>

// boost
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

CsvLoader * CsvLoader::instance = 0;

template <typename T>
std::ostream& operator<<(std::ostream & os, const std::vector<T> & v)
{
	for (int i = 1; i < v.size() - 1; i++)
	{
		os << v[i] << ";";
	}
	os << v[v.size() - 1];
	return os;

}

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
		temporaryRow->setData(row);
		allRows.push_back(*temporaryRow);
	}

	// 

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
	// if index > siezofRows or Negative:
	if (indexRowSorting > allRows[0].getNumberOfRows() || indexRowSorting < 0)
	{
		std::cerr << " ROW INDEX IS NOT VALID" << std::endl;
		return;
	}

	// get indexes:
	sortedIndexes = this->sortIndexes(this->getAllRowsDataByIndex(indexRowSorting));

}

template <typename T>
std::vector<std::size_t> CsvLoader::sortIndexes(const std::vector<T> &v)
{
	// initialize original index locations
	std::vector<std::size_t> idx(v.size());
	std::iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v
	std::sort(idx.begin(), idx.end(),
		[&v](std::size_t i1, std::size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

std::vector<std::string> CsvLoader::getAllRowsDataByIndex(int index)
{
	std::vector<std::string> allData;
	for (int i = 0; i < allRows.size(); i++)
	{
		allData.push_back(allRows[i].getRowData(index));
	}

	return allData;
}

void CsvLoader::writeCSV(std::ofstream & str)
{
	for (auto i = sortedIndexes.begin(); i < sortedIndexes.end() ; i++)
	{
		str << allRows[*i].getAllData();
		str << std::endl;
	}
}

void CsvLoader::sortingByNumber()
{
}

void CsvRow::setData(std::string data)
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
