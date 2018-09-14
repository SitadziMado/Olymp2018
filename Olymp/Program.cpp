#include <algorithm>
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

void solve()
{
	double a, b;
	cin >> a >> b;
	cout << a + b + 1.0 << endl;
}
