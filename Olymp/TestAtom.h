#pragma once

#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>

#include "Utility.h"

class ITestable
{
public: 
	virtual bool test(std::istream& programOutput) const = 0;
	static std::shared_ptr<ITestable> fromStream(
		std::istream& stream
	);

protected:
	ITestable() = default;

private:
};

template<typename T>
class TestAtom : ITestable
{
public:
	static std::shared_ptr<ITestable> fromStream(std::istream& stream);

	TestAtom() = default;
	TestAtom(T value);
	virtual bool test(std::istream& programOutput) const override final;

private:
	T value_;
};

template<typename T>
inline bool TestAtom<T>::test(std::istream& programOutput) const
{
	T value;
	programOutput >> value;
	return value_ == value;
}

template<typename T>
inline std::shared_ptr<ITestable> TestAtom<T>::fromStream(std::istream& stream)
{
	T temp;
	stream >> temp;

	ITestable* atom = new TestAtom<T>(temp);

	return std::shared_ptr<ITestable>(atom);
}

template<>
inline std::shared_ptr<ITestable> TestAtom<std::string>::fromStream(std::istream& stream)
{
	std::string temp;

	skipWhitespace(stream);
	std::getline(stream, temp);

	ITestable* atom = new TestAtom<std::string>(temp);

	return std::shared_ptr<ITestable>(atom);
}

template<typename T>
inline TestAtom<T>::TestAtom(T value) :
	value_(std::forward<T>(value))
{
}
