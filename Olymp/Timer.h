#pragma once

#include <chrono>
#include <utility>

using namespace std::chrono;
using namespace std::chrono_literals;

using i64 = long long;

class Timer
{
public:
	template<typename Func, typename... Args>
	nanoseconds measure(Func func, Args&&... args) const;
	template<typename Func, typename... Args>
	seconds measureSeconds(Func func, Args&&... args) const;
	template<typename Func, typename... Args>
	milliseconds measureMilliseconds(Func func, Args&&... args) const;

	Timer() = default;

private:
	high_resolution_clock hrc_ = high_resolution_clock();
	time_point<high_resolution_clock> previous_;
	nanoseconds duration_;
	bool isStarted_ = false;
};

template<typename Func, typename... Args>
inline nanoseconds Timer::measure(Func func, Args&&... args) const
{
	auto start = hrc_.now();
	func(std::forward<Args>(args)...);
	auto finish = hrc_.now();
	return duration_cast<nanoseconds>(finish - start);
}

template<typename Func, typename ...Args>
inline seconds Timer::measureSeconds(Func func, Args&& ...args) const
{
	return duration_cast<seconds>(measure(func, std::forward<Args>(args)...));
}

template<typename Func, typename ...Args>
inline milliseconds Timer::measureMilliseconds(Func func, Args&& ...args) const
{
	return duration_cast<milliseconds>(measure(func, std::forward<Args>(args)...));
}
