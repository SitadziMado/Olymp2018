#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

#include <clocale>

#ifdef HOME
#include "TestingSystem.h"
#endif // HOME

#define START_APP class App { public:
#define END_APP };
#endif // HOME

using i64 = long long;
using u64 = unsigned long long;

class App;

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

START_APP



void solve()
{

}



END_APP




