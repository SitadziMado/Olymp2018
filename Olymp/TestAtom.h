#pragma once

#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>

#include "Utility.h"

class ITestable
{
public: 
	struct TestingResults
	{
		TestingResults(bool correct, std::string&& string);

		operator bool() const;
		explicit operator const std::string&() const;

		TestingResults& merge(const TestingResults& rhs);
		TestingResults& append(const std::string& desc);

	private:
		bool correct_;
		std::string programOutput_;
	};

	static std::shared_ptr<ITestable> fromStream(
		std::istream& stream
	);

	virtual ~ITestable() = default;
	virtual TestingResults test(std::istream& programOutput) const = 0;
	virtual std::string toString() const = 0;
	
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
	TestingResults test(std::istream& programOutput) const override final;
	std::string toString() const override;

private:
	T value_;
};

template<typename T>
inline ITestable::TestingResults TestAtom<T>::test(std::istream& programOutput) const
{
	T value;
	programOutput >> value;
	return ITestable::TestingResults(value_ == value, std::to_string(value));
}

template<>
inline ITestable::TestingResults TestAtom<std::string>::test(std::istream& programOutput) const
{
	std::string value;
	skipWhitespace(programOutput);
	std::getline(programOutput, value);
	return ITestable::TestingResults(value_ == value, std::move(value));
}

template<typename T>
inline std::string TestAtom<T>::toString() const
{
	return std::to_string(value_);
}

template<>
inline std::string TestAtom<std::string>::toString() const
{
	return value_;
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