#include "Test.h"

#include <limits>
#include <sstream>
#include <string>
#include <utility>

#include "Utility.h"

std::shared_ptr<Test> Test::fromStream(std::istream& stream)
{
	ITestablePtrContainer atoms;
	std::string line;

	skipWhitespace(stream);

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

ITestable::TestingResults Test::test(std::istream& programOutput) const
{
	ITestable::TestingResults tr{ true, "" };

	for (auto&& a : atoms_)
	{
		auto nextTr = a->test(programOutput);

		if (!tr.merge(nextTr))
		{
			break;
		}
	}

	return tr;
}

std::string Test::getExpectedString() const
{
	std::string rv;
	rv.reserve(16 * atoms_.size());

	for (auto&& a : atoms_)
	{
		rv += /*"\t" +*/ a->toString() + "\n";
	}

	if (atoms_.size())
	{
		rv.pop_back();
	}

	return rv;
}