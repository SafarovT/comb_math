#include "quadraticAssignmentProblem.h"

namespace
{
	using namespace std;

    int CalculateTotalCost(const Matrix& facilities, const Matrix& locations, const vector<int>& assignment)
    {
        int totalCost = 0;
        int n = facilities.size();

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int facility1 = assignment[i];
                int facility2 = assignment[j];
                int location1 = i;
                int location2 = j;

                totalCost += facilities[facility1][facility2] * locations[location1][location2];
            }
        }

        return totalCost;
    }
}

ResultAssigment SolveQuadraticAssignmentProblem(Matrix facilities, Matrix locations)
{
    int n = facilities.size();
    vector<int> assignment(n);
    for (int i = 0; i < n; i++) {
        assignment[i] = i;
    }

    int minCost = CalculateTotalCost(facilities, locations, assignment);
    vector<int> minAssignment = assignment;

    while (next_permutation(assignment.begin(), assignment.end()))
    {
        int cost = CalculateTotalCost(facilities, locations, assignment);
        if (cost < minCost)
        {
            minCost = cost;
            minAssignment = assignment;
        }
    }

    return { minCost, minAssignment };
}