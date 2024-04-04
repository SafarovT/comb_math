#include "../../external/catch2/catch.hpp"
#include "../Task2/solveKnapsack.h"
#include <iostream>

TEST_CASE("Default data")
{
    GivenData data = {
        14,
        4,
        { 5, 10, 6, 5 },
        { 3, 5, 4, 2 },
    };
    
    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 2);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 3);
}

TEST_CASE("Empty items")
{
    GivenData data = {
        14,
        0,
        { },
        { },
    };

    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 0);
}

TEST_CASE("Heavy items")
{
    GivenData data = {
        10,
        5,
        { 100, 500, 400, 300, 11 },
        { 1, 1, 1, 1, 1 },
    };

    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 0);
}

TEST_CASE("All items fit")
{
    GivenData data = {
        5,
        5,
        { 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1 },
    };

    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 5);
}

TEST_CASE("Only last item fit")
{
    GivenData data = {
        15,
        5,
        { 100, 100, 100, 100, 15 },
        { 2, 2, 2, 2, 100 },
    };

    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 1);
    REQUIRE(result[0] == 5);
}

TEST_CASE("Large data test")
{
    GivenData data = {
        750,
        15,
        { 70, 73, 77, 80, 82, 87, 90, 94, 98, 106, 110, 113, 115, 118, 120 },
        {
            135,
            139,
            149,
            150,
            156,
            163,
            173,
            184,
            192,
            201,
            210,
            214,
            221,
            229,
            240,
        },
    };

    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 8);
    REQUIRE(result[0] == 1);
    REQUIRE(result[1] == 3);
    REQUIRE(result[2] == 5);
    REQUIRE(result[3] == 7);
    REQUIRE(result[4] == 8);
    REQUIRE(result[5] == 9);
    REQUIRE(result[6] == 14);
    REQUIRE(result[7] == 15);
}

TEST_CASE("")
{
    GivenData data = {
       20,
       6,
       { 1, 2, 3, 4, 5, 6 },
       { 1, 2, 3, 4, 5, 6 },
    };

    auto result = SolveKnapsack(data);

    REQUIRE(result.size() == 5);
    REQUIRE(result[0] == 2);
    REQUIRE(result[1] == 3);
    REQUIRE(result[2] == 4);
    REQUIRE(result[3] == 5);
    REQUIRE(result[4] == 6);
}