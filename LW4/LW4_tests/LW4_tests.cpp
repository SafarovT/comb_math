#include "../../external/catch2/catch.hpp"
#include <vector>
#include "../LW4/STCounter.h"

TEST_CASE("Simple test")
{
	int expected = 3;
	Matrix adj = {
		{ 0, 1, 0, 1 },
		{ 1, 0, 0, 1 },
		{ 0, 0, 0, 1 },
		{ 1, 1, 1, 0 },
	};
	STCounter counter(adj);
	counter.CountSpanningTrees();
	int result = counter.GetResult();

	REQUIRE(result == expected);
}

TEST_CASE("Test with 4x4")
{
	int expected = 8;
	Matrix adj = {
		{ 0, 1, 1, 0 },
		{ 1, 0, 1, 1 },
		{ 1, 1, 0, 1 },
		{ 0, 1, 1, 0 },
	};
	STCounter counter(adj);
	counter.CountSpanningTrees();
	int result = counter.GetResult();

	REQUIRE(result == expected);
}

TEST_CASE("Test with 5x5")
{
	int expected = 21;
	Matrix adj = {
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 1, 1, 0, 0 },
		{ 1, 0, 1, 0, 0 },
	};
	STCounter counter(adj);
	counter.CountSpanningTrees();
	int result = counter.GetResult();

	REQUIRE(result == expected);
}

TEST_CASE("Isolated vertex")
{
	int expected = 0;
	Matrix adj = {
		{ 0, 0, 0, 0 },
		{ 0, 0, 1, 1 },
		{ 0, 1, 0, 1 },
		{ 0, 1, 1, 0 },
	};
	STCounter counter(adj);
	counter.CountSpanningTrees();
	int result = counter.GetResult();

	REQUIRE(result == expected);
}

TEST_CASE("2 components")
{
	int expected = 0;
	Matrix adj = {
		{ 0, 1, 0, 0 },
		{ 1, 0, 0, 0 },
		{ 0, 0, 0, 1 },
		{ 0, 0, 1, 0 },
	};
	STCounter counter(adj);
	counter.CountSpanningTrees();
	int result = counter.GetResult();

	REQUIRE(result == expected);
}