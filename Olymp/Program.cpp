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

// Wi-Fi password: lab_po_3_204A

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

START_APP



void solve()
{

}



END_APP



