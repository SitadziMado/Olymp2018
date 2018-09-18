#include "Utility.h"

#include <locale>
#include <sstream>
#include <unordered_set>

#include <cctype>

std::string trim(const std::string& string)
{
	std::string rv;

	auto front = string.cbegin();

	while (front != string.cend() && std::isspace(*front))
	{
		++front;
	}

	if (front == string.cend())
	{
		rv = std::string();
	}
	else
	{
		auto back = string.cend() - 1;

		while (std::isspace(*back))
		{
			--back;
		}

		++back;

		rv = std::string(front, back);
	}

	return rv;
}

std::string& to_string(std::string& string)
{
	return string;
}

/*template<>
std::vector<std::string> split(
	const std::string& string,
	const std::unordered_set<char>& delimeters
)
{
	std::vector<std::string> rv;
	std::stringstream ss{ string };

	std::string temp;

	while (ss >> temp)
	{
		rv.push_back(temp);
	}

	return rv;
}*/

template<template<typename> typename TDelimeterContainer>
std::vector<std::string> split(
	const std::string& string,
	TDelimeterContainer<char>&& delimeters
)
{
	std::vector<std::string> rv;
	std::stringstream ss{ string };

	std::string temp;

	while (ss >> temp)
	{
		rv.push_back(temp);
	}

	return rv;
}

void skipWhitespace(std::istream& stream)
{
	while (std::isspace(stream.peek()))
	{
		stream.ignore(1);
	}
}
