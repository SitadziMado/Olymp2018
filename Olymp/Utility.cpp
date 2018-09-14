#include "Utility.h"

#include <sstream>

std::string trim(const std::string& string)
{
	std::string rv;

	auto front = string.cbegin();

	while (front != string.cend() && *front == ' ')
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

		while (/*back != string.cbegin() &&*/ *back == ' ')
		{
			--back;
		}

		++back;

		rv = std::string(front, back);
	}

	return rv;
}

std::vector<std::string> tokenize(const std::string& string)
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
