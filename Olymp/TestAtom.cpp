#include "TestAtom.h"

#include <iostream>
#include <string>
#include <unordered_map>

std::shared_ptr<ITestable> ITestable::fromStream(std::istream& stream)
{
	std::string typeSignature;
	std::shared_ptr<ITestable> rv;

	stream >> typeSignature;

	if (typeSignature == "i64")
	{
		rv = TestAtom<long long>::fromStream(stream);
	}
	else if (typeSignature == "double")
	{
		rv = TestAtom<double>::fromStream(stream);
	}
	else
	{
		throw std::runtime_error(
			"��� " + typeSignature + " �� ��������������."
		);
	}

	return rv;
}