#include "../../external/catch2/catch.hpp"
#include "../LW3/utils.h"
#include <sstream>

TEST_CASE("Testing {GetDualGraph}: Squar + Triangle")
{
	Graph graph(5);
	graph.AddEdge(0, 1);
	graph.AddEdge(1, 2);
	graph.AddEdge(2, 3);
	graph.AddEdge(0, 3);
	graph.AddEdge(1, 4);
	graph.AddEdge(2, 4);
	Graph dualGraph = GetDualGraph(graph);
	/*std::ostringstream output;
	std::string expectedOutput = "[]";
	dualGraph.PrintGraph(output);
	CHECK(output.str() == expectedOutput);*/
}

//TEST_CASE("Testing {GetDualGraph}: Default test")
//{
//	Graph graph(5);
//	graph.AddEdge(0, 1);
//	graph.AddEdge(0, 2);
//	graph.AddEdge(1, 2);
//	graph.AddEdge(2, 3);
//	graph.AddEdge(1, 3);
//	graph.AddEdge(1, 4);
//	graph.AddEdge(4, 3);
//	Graph dualGraph = GetDualGraph(graph);
//	std::ostringstream output;
//	std::string expectedOutput = "[(0,1), (0,2), (1,0), (0,3), (0,3), (1,2), (2,3)]";
//	dualGraph.PrintGraph(output);
//	CHECK(output.str() == expectedOutput);
//}