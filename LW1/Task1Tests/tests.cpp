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

TEST_CASE("Every next price is prev multiplied by 2")
{
    Matrix facilities = {
       {0, 2, 4, 8},
       {2, 0, 16, 32},
       {4, 16, 0, 64},
       {8, 32, 64, 0}
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
    REQUIRE(result.totalCost == 252);
}
