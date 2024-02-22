#include "../../external/catch2/catch.hpp"
#include "../Task2/solveKnapsack.h"

TEST_CASE("Default data")
{
    GivenData data = {
        13,
        5,
        { 3, 4, 5, 8, 9 },
        { 1, 6, 4, 7, 6 },
    };
    
    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 4);
}