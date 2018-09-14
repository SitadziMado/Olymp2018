#pragma once

#include <iosfwd>
#include <string>
#include <vector>

std::string trim(const std::string& string);
std::vector<std::string> tokenize(const std::string& string);
void skipWhitespace(std::istream& stream);