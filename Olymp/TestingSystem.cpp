#include "TestingSystem.h"

#include <iostream>

TestingSystem::TestingSystem()
{
}

void TestingSystem::run(std::function<void()> solveProc)
{
	auto in = std::ifstream("input.txt");
	auto out = std::stringstream();

	auto cinBuffer = std::cin.rdbuf(in.rdbuf());
	auto coutBuffer = std::cout.rdbuf(out.rdbuf());

	timer_.start();
	solveProc();
	timer_.stop();

	// check(std::ifstream("input.txt"), out);

	std::cin.rdbuf(cinBuffer);
	std::cout.rdbuf(coutBuffer);
}

void TestingSystem::check(std::ifstream & testStream, std::stringstream & output)
{
}
