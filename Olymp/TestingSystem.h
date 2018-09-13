#pragma once

#include <fstream>
#include <functional>
#include <sstream>

#include "Timer.h"

class TestingSystem
{
public:
	TestingSystem();
	void run(std::function<void()> solveProc);

private:
	void check(std::ifstream& testStream, std::stringstream& output);

	Timer timer_;
};