#include "../../external/catch2/catch.hpp"
#include "../LW3/utils.h"
#include <sstream>

TEST_CASE("Testing {GetDualGraph}: Simple graph")
{
    std::vector<Vertex> vertices =
    {
        Vertex(1, Point2D(-4, 4)),
        Vertex(2, Point2D(-1, 5)),
        Vertex(3, Point2D(3, 4)),
        Vertex(4, Point2D(4, 1)),
        Vertex(5, Point2D(0, -2)),
        Vertex(6, Point2D(-1, 3)),
        Vertex(7, Point2D(2, 2)),
    };

    std::vector<std::vector<int>> graphAdj =
    {
        {1, 2}, {1, 6}, {1, 5}, {2, 6}, {2, 3}, {3, 7}, {7, 4}, {3, 4}, {5, 4}, {6, 5},
    };
    GraphStruct graph = { vertices, graphAdj };
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