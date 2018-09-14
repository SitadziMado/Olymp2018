#pragma once

#include <iosfwd>
#include <memory>
#include <vector>

#include "TestAtom.h"

class Test
{
public:
	static std::shared_ptr<Test> fromStream(std::istream& stream);

	Test() = default;
	bool test(std::istream& programOutput) const;

private:
	using ITestablePtr = std::shared_ptr<ITestable>;
	using ITestablePtrContainer = std::vector<ITestablePtr>;

	template<class TContainer>
	Test(TContainer&& atoms);

	ITestablePtrContainer atoms_;
};

template<class TContainer>
inline Test::Test(TContainer&& atoms) :
	atoms_(std::forward<TContainer>(atoms))
{
}
