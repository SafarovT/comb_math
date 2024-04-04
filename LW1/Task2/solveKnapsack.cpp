#include "solveKnapsack.h"
#include <math.h>
#include <iostream>
#include <algorithm>

namespace
{
	using namespace std;
	
	bool GenerateNextPermutation(vector<int>& itemsToPick)
	{
		int i = itemsToPick.size() - 1;
		while (i >= 0)
		{
			itemsToPick[i]--;
			if (itemsToPick[i] == 0)
			{
				return true;
			}
			itemsToPick[i] = 1;
			i--;
		}

		return false;
	}

	int GetTotalPrice(GivenData const& givenData, vector<int> const& itemsToPick)
	{
		int weight = 0;
		int price = 0;
		for (int i = 0; i < itemsToPick.size(); i++)
		{
			if (itemsToPick[i] == 1)
			{
				weight += givenData.weights[i];
				price += givenData.prices[i];
				if (weight > givenData.maxWeight)
				{
					return -1;
				}
			}
		}
		return price;
	}

	vector<int> GetResultItemsSet(vector<int> const& itemsToPick)
	{
		vector<int> resultSet;

		for (int i = 0; i < itemsToPick.size(); i++)
		{
			if (itemsToPick[i] == 1)
			{
				resultSet.push_back(i + 1);
			}
		}

		return resultSet;
	}

	void PrintVector(vector<int> const& vec)
	{
		for (auto const& item : vec)
		{
			cout << item << " ";
		}
		cout << endl;
	}
}


vector<int> SolveKnapsack(GivenData const& givenData)
{
	vector<int> itemsToPick(givenData.itemsCount, 1);

	vector<int> bestSet = {};
	int maxPrice = -1;
	do
	{
		int newPrice = GetTotalPrice(givenData, itemsToPick);
		if (newPrice > maxPrice)
		{
			maxPrice = newPrice;
			bestSet = itemsToPick;
		}
	} while (GenerateNextPermutation(itemsToPick));

	return GetResultItemsSet(bestSet);
}