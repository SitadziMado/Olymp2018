#include "Timer.h"

#include <stdexcept>

Timer::Timer()
{
}

void Timer::start()
{
	if (!isStarted_)
	{
		previous_ = hrc_.now();
	}
}

void Timer::stop()
{
	auto now = hrc_.now();
	duration_ = now - previous_;

	if (!isStarted_)
	{
		throw new std::runtime_error(
			"Таймер не запущен."
		);
	}

	isStarted_ = false;
}

i64 Timer::getMilliseconds() const
{
	if (isStarted_)
	{
		throw new std::runtime_error(
			"Таймер запущен."
		);
	}

	return duration_cast<milliseconds>(duration_).count();
}

i64 Timer::getSeconds() const
{
	if (isStarted_)
	{
		throw new std::runtime_error(
			"Таймер запущен."
		);
	}

	return duration_cast<seconds>(duration_).count();
}
