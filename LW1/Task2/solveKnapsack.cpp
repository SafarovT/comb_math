#include "solveKnapsack.h"
#include <math.h>
#include <iostream>

std::vector<int> answer;

namespace
{
	using namespace std;

	GivenData data;
	vector<vector<int>> table;

	void Init(GivenData const& givenData)
	{
		data = givenData;
		for (size_t i = 0; i < data.itemsCount; i++)
		{
			table.push_back({});
			for (size_t j = 0; j < data.maxWeight; j++)
			{
				table[i].push_back(0);
			}
		}

		for (size_t i = 1; i < data.itemsCount; i++)
		{
			for (size_t j = 1; j < data.maxWeight; j++)
			{
				if (j >= data.weights[i])
				{
					table[i][j] = max(table[i - 1][j], table[i - 1][j - data.weights[i]] + data.prices[i]);
				}
				else
				{
					table[i][j] = table[i - 1][j];
				}
			}
		}
	}

	void SolveKnapsackRecursive(int k, int s) // k = item, s = weight
	{
		if (table[k][s] == 0)
		{
			return;
		}

		if (table[k - 1][s] == table[k][s])
		{
			SolveKnapsackRecursive(k - 1, s);
		}
		else
		{
			SolveKnapsackRecursive(k - 1, s - data.weights[k]);
			cout << "here " << k << endl;
			answer.push_back(k);
		}
	}
}


vector<int> SolveKnapsack(GivenData const& givenData)
{
	Init(givenData);

	SolveKnapsackRecursive(1, 1);

	return answer;
}