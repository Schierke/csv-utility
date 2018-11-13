#pragma once
#ifndef  CONFIG_H
#define  CONFIG_H

#include <map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <cstdlib>


#define ASSERT_WITH_MSG(cond, msg) do \
{ if (!(cond)) { std::ostringstream str; str << msg; std::cout << str.str(); std::abort(); } \
} while(0)

namespace Config
{

	enum METHOD
	{
		SORTING_BY_ROW,
		SORTING_BY_NUMBER
	};

	enum ORDER
	{
		ASCENDING,
		DESCENDING
	};

	template <typename T>
	class EnumParser
	{
	private:
		std::map<std::string, T> enumMap;
	public:
		EnumParser() {};

		T parseSomeEnum(const std::string & value)
		{
			typename std::map<std::string, T>::const_iterator iValue = enumMap.find(value);
			if (iValue == enumMap.end())
				std::cerr<< "ERROR, CANT MAP THE VALUE";
			return iValue->second;
		}
	};

	EnumParser<METHOD>::EnumParser()
	{
		enumMap["SORTING_BY_ROW"] = SORTING_BY_ROW;
		enumMap["SORTING_BY_NUMBER"] = SORTING_BY_NUMBER;
	}

	EnumParser<ORDER>::EnumParser()
	{
		enumMap["ASCENDING"] = ASCENDING;
		enumMap["DESCENDING"] = DESCENDING;
	}

}
#endif // ! CONFIG_H

