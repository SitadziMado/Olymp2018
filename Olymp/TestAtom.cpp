#include "TestAtom.h"

#include <iostream>
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
	else if (typeSignature == "string")
	{
		rv = TestAtom<std::string>::fromStream(stream);
	}
	else
	{
		throw std::runtime_error(
			"Тип " + typeSignature + " не поддерживается."
		);
	}

	return rv;
}

ITestable::TestingResults::TestingResults(bool correct, std::string&& string) :
	correct_(correct),
	programOutput_(string)
{}

ITestable::TestingResults::operator bool() const
{
	return correct_;
}

ITestable::TestingResults::operator const std::string&() const
{
	return programOutput_;
}

ITestable::TestingResults& ITestable::TestingResults::merge(const TestingResults& rhs)
{
	correct_ &= rhs.correct_;
	append(rhs.programOutput_);
	return *this;
}

ITestable::TestingResults& ITestable::TestingResults::append(const std::string& desc)
{
	programOutput_ += (programOutput_.empty() ? "" : "\n") + desc;
	return *this;
}
