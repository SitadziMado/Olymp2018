#pragma once

#include <iosfwd>
#include <sstream>
#include <string>
#include <vector>

std::string trim(const std::string& string);
void skipWhitespace(std::istream& stream);
std::string readAll(std::istream& stream);

template<template<typename> typename TDelimeterContainer>
inline std::vector<std::string> split(
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

template<typename T>
inline std::string show(T&& value)
{
	std::stringstream ss;
	ss << value;

	std::string rv = "\"";
	std::string line;

	while (std::getline(ss, line))
	{
		rv += line + "\n";
	}

	rv.pop_back();
	rv += "\"";

	return rv;
}