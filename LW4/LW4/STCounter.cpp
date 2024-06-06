#include "STCounter.h"

namespace
{
	using namespace std;
	const double EPS = 1E-9;
}

double STCounter::GetDeterminant(Matrix& matrix)
{
	size_t size = matrix.size();
	for (int col = 0; col < size; col++)
	{
		bool found = false;
		for (int row = col; row < size; row++)
		{
			if (abs(matrix[row][col]) > EPS)
			{
				if (row != col)
					matrix[row].swap(matrix[col]);
					found = true;
				break;
			}
		}

		if (!found)
			return 0;

		for (int row = col + 1; row < size; row++)
		{
			while (true)
			{
				int del = matrix[row][col] / matrix[col][col];;
				for (int j = col; j < size; j++)
					matrix[row][j] -= del * matrix[col][j];
				if (matrix[row][col] == 0)
					break;
				else
					matrix[row].swap(matrix[col]);
			}
		}
	}

	double res = 1;

	for (int i = 0; i < size; i++)
	{
		res *= matrix[i][i];
	}
	return abs(res);
}

Matrix STCounter::GetMinor(const Matrix& matrix, int row, int column)
{
	size_t minorLength = matrix.size() - 1;
	Matrix minor(minorLength, vector<double>(minorLength, 0));

	int dI = 0, dJ = 0;
	for (size_t i = 0; i <= minorLength; i++)
	{
		dJ = 0;
		for (size_t j = 0; j <= minorLength; j++)
		{
			if (i == row)
			{
				dI = 1;
				break;
			}
			else if (j == column)
				dJ = 1;
			else
				minor[i - dI][j - dJ] = matrix[i][j];
		}
	}
	return minor;
}

STCounter::STCounter(Matrix const& matrix)
	: m_adj(matrix)
	, m_laplacian(Matrix(matrix.size(), vector<double>(matrix.size(), 0)))
{}

void STCounter::CountSpanningTrees()
{
	size_t vertexesCount = m_adj.size();
	int degree;
	for (size_t i = 0; i < vertexesCount; i++)
	{
		degree = 0;
		for (size_t j = 0; j < vertexesCount; j++)
		{
			degree += m_adj[i][j];
			m_laplacian[i][j] = -m_adj[i][j];
		}
		m_laplacian[i][i] = degree;
	}

	Matrix minor = GetMinor(m_laplacian, 0, 0);
	m_spanningTreesNumber = GetDeterminant(minor);
}

int STCounter::GetResult() const
{
	return m_spanningTreesNumber;
}