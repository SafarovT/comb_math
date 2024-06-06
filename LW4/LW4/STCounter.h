#pragma once
#include <vector>
#include <iostream>

using Matrix = std::vector<std::vector<double>>;

class STCounter
{
public:
	STCounter(Matrix const& matrix);
	void CountSpanningTrees();
	int GetResult() const;

	static double GetDeterminant(Matrix& matrix);
	static Matrix GetMinor(const Matrix& matrix, int row, int column);
private:

	Matrix m_adj, m_laplacian;
	int m_spanningTreesNumber = 0;
};