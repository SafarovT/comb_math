#include <iostream>
#include <vector>
#include "STCounter.h"

namespace
{
	using namespace std;
}

int main()
{
	vector<vector<int>> adj = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 0 },
		{ 1, 1, 0, 1 },
		{ 0, 0, 1, 0 }
	};

	STCounter counter(adj);
	counter.CountSpanningTrees();
	auto result = counter.GetResult();
	cout << "Answer: " << result << endl;
	return 0;
}