#pragma once

#include <iosfwd>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

template<typename T>
using Ptr = std::shared_ptr<T>;

std::string trim(const std::string& string);
void skipWhitespace(std::istream& stream);

template<template<typename> class TDelimeterContainer>
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

template<typename T>
std::string show(T&& value)
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

template<typename T, typename... TArgs>
Ptr<T> alloc(TArgs&&... args)
{
    return std::make_shared<T>(std::forward<TArgs>(args)...);
}

template<typename T>
std::string show(T value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}