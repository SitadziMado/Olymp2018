#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <cctype>
#include <clocale>

#ifdef HOME
#include "TestingSystem.h"

#define START_APP class App { public:
#define END_APP };
using i128 = long long;
#else
#define START_APP
#define END_APP
// using i128 = __int128;
#endif // HOME


using i64 = long long;
using u64 = unsigned long long;

#ifdef HOME
class App;
#else 
void solve();
#endif

int main(int argc, char** argv)
{
	std::ios_base::sync_with_stdio(false);

#ifdef HOME
	std::setlocale(LC_ALL, "ru-RU");

	auto ts = TestingSystem();

	ts.test<App>(
		(std::istream&)std::ifstream("input.txt"),
		(std::istream&)std::ifstream("tests.txt")
	);
#else
	solve();
#endif // HOME

	return 0;
}

using namespace std;

int cmp(double lhs, double rhs)
{
	static const auto eps = 0.00000001;

	const auto diff = rhs - lhs;

	if (abs(diff) < eps)
	{
		return 0;
	}
	else if (lhs < rhs)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

START_APP

struct Transaction
{
	i64 time;
	double value;
};

struct Block
{
	Block(vector<Transaction>&& init) :
		transactions(move(init))
	{
		time = transactions.back().time;

		for (auto&& a : transactions)
		{
			sum += a.value;
			additionalSum += a.value * (time - a.time);
		}
	}

	static const size_t Size = 448;

	i64 time;
	double sum = 0;
	double additionalSum = 0;
	vector<Transaction> transactions;
};

struct Account
{
	void addTransaction(const Transaction& trans)
	{
		tail.push_back(trans);

		if (tail.size() == Block::Size)
		{
			blocks.push_back(Block(move(tail)));
			tail = {};
		}
	}

	double removeTransaction(const Transaction& trans)
	{
		auto time = trans.time;
		auto value = trans.value;
		double partial = 0;

	repeat:
		i64 size = tail.size() - 1;

		for (i64 i = size; i >= 0 && value > 0.; --i)
		{
			auto& cur = tail[i];

			switch (cmp(value, cur.value))
			{
			case 1:
			case 0:
				partial += cur.value * (time - cur.time);
				value -= cur.value;
				tail.pop_back();
				break;
			case -1:
				partial += value * (time - cur.time);
				cur.value -= value;
				value = 0.;
				break;
			default: break;
			}
		}

		while (cmp(value, 0.) > 0)
		{
			auto& last = blocks.back();

			switch (cmp(last.sum, value))
			{
			case 1:
				tail = move(last.transactions);
				blocks.pop_back();
				goto repeat;
			case 0:
				partial += last.additionalSum + last.sum * (time - last.time);
				value -= last.sum;
				blocks.pop_back();
				break;
			case -1:
				partial += last.additionalSum + last.sum * (time - last.time);
				value -= last.sum;
				blocks.pop_back();
				break;
			default: break;
			}
		}

		return partial;
	}

	vector<Block> blocks;
	vector<Transaction> tail;
};

void skipWhitespace(std::istream& stream)
{
	while (std::isspace(stream.peek()))
	{
		stream.ignore(1);
	}
}

void solve()
{
	map<string, Account> accounts;
	string line;

	while (getline(cin, line))
	{
		stringstream ss{ line };

		char null;
		i64 time;
		string sender, receiver;
		double value;

		ss >> time >> null >> sender;
		skipWhitespace(ss);
		ss >> null >> value >> null >> receiver;

		Transaction trans = { time, value };

		if (sender != "00000000")
		{
			cout << fixed<<setprecision(6)<<accounts[sender].removeTransaction(trans) / (60. * 60. * 24.) << endl;
		}
		else
		{
			cout << 0 << endl;
		}

		if (!accounts.count(receiver))
		{
			accounts[receiver] = Account();
		}

		accounts[receiver].addTransaction(trans);
	}
}



END_APP



