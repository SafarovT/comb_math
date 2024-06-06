#include "../../external/catch2/catch.hpp"
#include "../LW5/BipGraph.h"

TEST_CASE("Test with 4x4")
{
	BipGraph g(4, 4);
	g.AddEdge(1, 2);
	g.AddEdge(1, 3);
	g.AddEdge(2, 1);
	g.AddEdge(3, 2);
	g.AddEdge(4, 2);
	g.AddEdge(4, 4);

	int result = g.HopcroftKarp();

	int expected = 4;

	REQUIRE(result == expected);
}

TEST_CASE("Test with 7x7")
{
	BipGraph g(7, 7);
	g.AddEdge(1, 1);
	g.AddEdge(1, 3);
	g.AddEdge(2, 1);
	g.AddEdge(2, 4);
	g.AddEdge(2, 7);
	g.AddEdge(3, 3);
	g.AddEdge(3, 5);
	g.AddEdge(3, 6);
	g.AddEdge(4, 4);
	g.AddEdge(5, 3);
	g.AddEdge(6, 2);
	g.AddEdge(6, 5);
	g.AddEdge(7, 1);

	int result = g.HopcroftKarp();

	int expected = 6;

	REQUIRE(result == expected);
}