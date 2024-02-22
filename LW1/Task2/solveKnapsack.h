#pragma once
#include <vector>

struct GivenData
{
    unsigned maxWeight;
    size_t itemsCount;
    std::vector<int> weights;
    std::vector<int> prices;
};

std::vector<int> SolveKnapsack(GivenData const& data);