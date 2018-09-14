#pragma once

#include <iosfwd>
#include <string>
#include <vector>

template<template<typename> typename TDelimeterContainer>
std::vector<std::string> split(
	const std::string& string,
	TDelimeterContainer<char>&& delimeters
);

std::string trim(const std::string& string);
void skipWhitespace(std::istream& stream);