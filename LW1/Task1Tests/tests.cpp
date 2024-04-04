#include "../../external/catch2/catch.hpp"
#include "../Task1/quadraticAssignmentProblem.h"

#include <iostream>

TEST_CASE("Default matrixes")
{
    Matrix facilities = {
        {0, 2, 3, 1},
        {2, 0, 1, 4},
        {3, 1, 0, 2},
        {1, 4, 2, 0}
    };

    Matrix locations = {
        {0, 1, 2, 3},
        {1, 0, 4, 2},
        {2, 4, 0, 1},
        {3, 2, 1, 0}
    };
    std::vector<MatrixElement> neededData = { 0, 2, 1, 3 };
    auto result = SolveQuadraticAssignmentProblem(facilities, locations);

    REQUIRE(result.assignment.size() == neededData.size());
    for (size_t i = 0; i < neededData.size(); i++)
    {
        REQUIRE(result.assignment[i] == neededData[i]);
    }
    REQUIRE(result.totalCost == 44);
}

TEST_CASE("All 1 except diagonal")
{
    Matrix facilities = {
       {0, 1, 1, 1},
       {1, 0, 1, 1},
       {1, 1, 0, 1},
       {1, 1, 1, 0}
    };

    Matrix locations = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };
    std::vector<MatrixElement> neededData = { 0, 1, 2, 3 };
    auto result = SolveQuadraticAssignmentProblem(facilities, locations);

    REQUIRE(result.assignment.size() == neededData.size());
    for (size_t i = 0; i < neededData.size(); i++)
    {
        REQUIRE(result.assignment[i] == neededData[i]);
    }
    REQUIRE(result.totalCost == 12);
}

TEST_CASE("Числа фибоначи")
{
    Matrix facilities = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0},
    };

    Matrix locations = {
        {0, 1, 2, 3},
        {5, 0, 8, 13},
        {21, 34, 0, 55},
        {89, 144, 233, 0},
    };
    std::vector<MatrixElement> neededData = { 0, 1, 2, 3 };
    auto result = SolveQuadraticAssignmentProblem(facilities, locations);

    REQUIRE(result.assignment.size() == neededData.size());
    for (size_t i = 0; i < neededData.size(); i++)
    {
        REQUIRE(result.assignment[i] == neededData[i]);
    }
    REQUIRE(result.totalCost == 608);
}

TEST_CASE("Test with one high value way")
{
    Matrix facilities = {
        {0, 5, 20, 30},
        {5, 0, 10, 15},
        {20, 10, 0, 200},
        {30, 15, 200, 0},
    };

    Matrix locations = {
        {0, 10, 15, 15},
        {10, 0, 2, 50},
        {15, 2, 0, 20},
        {15, 50, 20, 0},
    };
    std::vector<MatrixElement> neededData = { 0, 2, 3, 1 };
    auto result = SolveQuadraticAssignmentProblem(facilities, locations);

    REQUIRE(result.assignment.size() == neededData.size());
    for (size_t i = 0; i < neededData.size(); i++)
    {
        REQUIRE(result.assignment[i] == neededData[i]);
    }
    REQUIRE(result.totalCost == 3850);
}
