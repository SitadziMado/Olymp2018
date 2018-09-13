#pragma once

#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

using i64 = long long;

class Timer
{
public:
	Timer();
	void start();
	void stop();
	i64 getMilliseconds() const;
	i64 getSeconds() const;

private:
	high_resolution_clock hrc_ = high_resolution_clock();
	time_point<high_resolution_clock> previous_;
	nanoseconds duration_;
	bool isStarted_ = false;
};
