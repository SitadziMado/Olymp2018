#include "Test.h"

#include <limits>
#include <sstream>
#include <string>

#include <cctype>

#include "Utility.h"

std::shared_ptr<Test> Test::fromStream(std::istream& stream)
{
	ITestablePtrContainer atoms;
	std::string line;

	while (std::isspace(stream.peek()))
	{
		stream.ignore(1);
	}

	std::getline(stream, line);

	if (trim(line) == "begin")
	{
		while (std::getline(stream, line) && trim(line) != "end")
		{
			std::stringstream ss{ line };
			atoms.push_back(ITestable::fromStream(ss));
		}
	}

	auto entity = new Test(std::move(atoms));

	return std::unique_ptr<Test>(entity);
}

bool Test::test(std::istream& programOutput) const
{
	bool rv = true;

	for (auto&& a : atoms_)
	{
		if (!a->test(programOutput))
		{
			rv = false;
			break;
		}
	}

	return rv;
}
