#pragma once

#include <fstream>
#include <functional>
#include <sstream>

#include "Test.h"
#include "Timer.h"
#include "Utility.h"

class TestingSystem
{
public:
	template<class TApp>
	void test(
		std::istream& istream, 
		std::istream& testStream
	);

	TestingSystem() = default;

private:
	Timer timer_;
};

template<class TApp>
inline void TestingSystem::test(std::istream& istream, std::istream & testStream)
{
	auto ss = std::stringstream();

	// ��������� ������.
	auto cinBuffer = std::cin.rdbuf(istream.rdbuf());
	auto coutBuffer = std::cout.rdbuf(ss.rdbuf());

	size_t testCount;

	testStream >> testCount;

	for (size_t t = 0; t < testCount; ++t)
	{
		auto app = TApp();
		auto test = Test::fromStream(testStream);

		// ������� ����� ���������� ����.
		auto ms = timer_.measureMilliseconds(
			[&app]() { app.solve();  }
		).count();

		if (!test->test(ss))
		{
			std::cerr << "������������ ����� �� ����� �" << t + 1 << ". " << std::endl;
			// std::cerr << "\t" << R"(���������: ")" <<  << R"(";)";
		}
		else
		{
			std::cerr << "���� �" << t + 1 << ": ��. ";
		}

		std::cerr << "�����: " << ms << " ��." << std::endl;

		skipWhitespace(istream);
	}

	std::cin.rdbuf(cinBuffer);
	std::cout.rdbuf(coutBuffer);
}
