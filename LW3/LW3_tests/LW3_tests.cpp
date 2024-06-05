#include "../../external/catch2/catch.hpp"
#include "../LW3/utils.h"
#include <sstream>

TEST_CASE("Testing {GetGraphFaces}: Simple graph")
{
    Graph::GraphFaces expectedOutput = { {1, 2, 3, 4, 5}, {2, 1, 6}, {6, 1, 5}, {2, 6, 5, 4, 7, 3}, {3, 7, 4} };
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
	auto faces = GetGraphFaces(graph);
    CHECK(faces == expectedOutput);
}

//TEST_CASE("Testing {GetDualGraph}: Simple faces")
//{
//    GraphFaces faces = { {1, 2, 3, 4, 5}, {5, 2, 1}, {4, 5, 2}, {4, 2, 3} };
//    Graph dualGraph = GetDualGraph(faces);
//    for (int i = 0; i < dualGraph.GetSize(); i++)
//    {
//        std::cout << "Vertex " << i << ": ";
//        auto adj = dualGraph.GetAdj(i);
//        for (auto& v : adj)
//        {
//            std::cout << v << ", ";
//        }
//        std::cout << std::endl;
//    }
//}

TEST_CASE("Testing {GetDualGraph}: Simple faces")
{
    std::vector<std::vector<int>> expectedOutput = { {2, 2, 1, 1}, {0, 0, 2}, {0, 0, 1} };
    Graph::GraphFaces faces = { {1, 2, 3, 4}, {1, 3, 4}, {1, 2, 3} };
    Graph graph(faces);
    graph.ToDual();
    for (int i = 0; i < graph.GetSize(); i++)
    {
        auto adj = graph.GetAdj(i);
        for (int j = 0; j < adj.size(); j++)
        {
            CHECK(expectedOutput[i][j] == adj[j]);
        }
    }
}

TEST_CASE("Testing {ColorGraph}: Presentation test")
{
    std::vector<int> expectedOutput = { 0, 1, 2, 0, 2, 1, 0, 0, 3};
    Graph g(9);
    g.AddEdge(0, 5);
    g.AddEdge(0, 1);
    g.AddEdge(0, 2);
    g.AddEdge(1, 3);
    g.AddEdge(1, 4);
    g.AddEdge(1, 6);
    g.AddEdge(2, 3);
    g.AddEdge(2, 5);
    g.AddEdge(3, 4);
    g.AddEdge(3, 5);
    g.AddEdge(4, 5);
    g.AddEdge(4, 6);
    g.AddEdge(4, 8);
    g.AddEdge(5, 8);
    g.AddEdge(6, 8);
    g.AddEdge(7, 8);
    auto colors = ColorGraph(g);
    CHECK(colors == expectedOutput);
}

TEST_CASE("Simple triangle full algo")
{
    std::vector<int> expectedOutput = { 0, 1 };
    Graph g({{ 1, 2, 3 }, { 3, 2, 1 }});
    g.ToDual();
    auto colors = ColorGraph(g);
    CHECK(colors == expectedOutput);
}