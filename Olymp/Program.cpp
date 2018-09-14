#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <numeric>
#include <set>

#include <clocale>

#include "TestingSystem.h"

using i64 = long long;
using u64 = unsigned long long;

void solve();

int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "ru-RU");
	std::ios_base::sync_with_stdio(false);

#ifdef HOME
	auto ts = TestingSystem();

	ts.test(
		solve,
		std::ifstream("input.txt"), 
		std::ifstream("tests.txt")
	);
#else
	solve();
#endif // HOME

	return 0;
}

using namespace std;

struct Point
{
	i64 x;
	i64 y;
	size_t id;
};

void solve()
{
	size_t t;

	cin >> t;

	for (size_t i = 0; i < t; i++)
	{
		i64 hrs, mins;
		cin >> hrs >> mins;

		char u, t, c;
		double offset;

		cin >> u >> t >> c >> offset;
		offset -= 8.;

		i64 offsetMins = (i64)(round(offset * 60.));

		mins += hrs * 60;

		mins += offsetMins;

		mins = (mins + 1440) % 1440;
		hrs = mins / 60;
		mins %= 60;

		cout << setw(2) << setfill('0');

		cout << hrs << ":" << mins << endl;

		// printf("%02lld:%02lld\n", hrs, mins);
		// cout << hrs << ":" << mins << endl;
	}

	for (size_t i = 0; i < 10000000; i++)
	{
		int a = 0, b = 1;
		swap(a, b);
	}
}
