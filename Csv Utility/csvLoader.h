#pragma once

#ifndef CSVLOADER_H
#define CSVHOADER_H

#include "config.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

/*
Class for handling single row of csv file
*/

class CsvRow
{
private:
	std::vector<std::string> m_data; // data of each row, one element presents a Cell 
public:
	CsvRow() {};
	~CsvRow() {};

	void setData(std::string data);
	std::string getRowData(int index);

	inline int getNumberOfRows() const
	{
		return m_data.size();
	}
	inline std::vector<std::string> getAllData() const
	{
		return m_data;
	}
	// Debugging
	void printData();

};

/*
Class for loading and pre-processing csv loader, fetching csv datas to our database
*/
class CsvLoader
{
	// singleton
public:
	static CsvLoader* getInstance();

private:
	CsvLoader();
	static CsvLoader* instance;
	std::vector<CsvRow> allRows;
	std::vector<std::size_t> sortedIndexes;

public:
	CsvLoader(CsvLoader const&) = delete;
	void operator=(CsvLoader const&) = delete;

	// processing
	void readCSV(std::ifstream& str);
	void processingMethod(const std::string & processingMethod, const std::string & parameter);
	void sortingByRow(int indexRowSorting);
	void sortingByNumber();
	std::vector<std::string> getAllRowsDataByIndex(int index);
	void writeCSV(std::ofstream& str);


	template<typename T>
	std::vector<std::size_t> sortIndexes(const std::vector<T> &v);
	
};



#endif