#pragma once

#include <fstream>
#include <functional>
#include <sstream>

#include "Test.h"
#include "Timer.h"

class TestingSystem
{
public:
	template<typename TCallable, typename TInputStream, typename TTestStream>
	void test(TCallable&& func, TInputStream&& istream, TTestStream&& testStream);

	TestingSystem();

private:
	Timer timer_;
};

template<typename TCallable, typename TInputStream, typename TTestStream>
inline void TestingSystem::test(
	TCallable&& func,
	TInputStream&& istream, 
	TTestStream&& testStream
)
{
	auto ss = std::stringstream();

	// ��������� ������.
	auto cinBuffer = std::cin.rdbuf(istream.rdbuf());
	auto coutBuffer = std::cout.rdbuf(ss.rdbuf());

	size_t testCount;

	testStream >> testCount;
	// testStream.ignore();

	for (size_t t = 0; t < testCount; ++t)
	{
		auto test = Test::fromStream(testStream);
		auto ms = timer_.measureMilliseconds(func).count();
		
		if (!test->test(ss))
		{
			std::cerr << "������������ ����� �� ����� �" << t + 1 << ". ";
		}
		else
		{
			std::cerr << "���� �" << t + 1 << ": ��. ";
		}

		std::cerr << "�����: " << ms << "." << std::endl;
	}

	std::cin.rdbuf(cinBuffer);
	std::cout.rdbuf(coutBuffer);
}
