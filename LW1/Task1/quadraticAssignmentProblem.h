#pragma once
#include <algorithm>
#include <vector>

using MatrixElement = double;
using Matrix = std::vector<std::vector<MatrixElement>>;
struct ResultAssigment
{
	int totalCost;
	std::vector<int> assignment;
};

ResultAssigment SolveQuadraticAssignmentProblem(Matrix facilities, Matrix locations);