#include "utils.h"
#include <fstream>
#include <algorithm>

#include "GraphFaces.h"

namespace
{
	using namespace std;
}

Graph GetDualGraph(Graph const& graph)
{
    Graph dualGraph;
    
    // MAIN

    vector<Vertex> vertices =
    {
        Vertex(1, Point2D(-4, 4)),
        Vertex(2, Point2D(-1, 5)),
        Vertex(3, Point2D(3, 4)),
        Vertex(4, Point2D(4, 1)),
        Vertex(5, Point2D(0, -2)),
        Vertex(6, Point2D(-1, 3)),
        Vertex(7, Point2D(2, 2)),
    };

    vector<vector<int>> graphAdj =
    {
        {1, 2}, {1, 6}, {1, 5}, {2, 6}, {2, 3}, {3, 7}, {7, 4}, {3, 4}, {5, 4}, {6, 5},
    };
    vector<Edge> edges;
    edges.resize(graphAdj.size() * 2); // HZ
    for (int i = 0; i < graphAdj.size(); i++)
    {
        Vertex from = vertices[graphAdj[i][0] - 1];
        Vertex to = vertices[graphAdj[i][1] - 1];
        edges[2 * i] = Edge(from, to);
        edges[2 * i + 1] = Edge(to, from);

        edges[2 * i].SetReverseEdge(edges[2 * i + 1]);
        edges[2 * i + 1].SetReverseEdge(edges[2 * i]);
    }

    for (Vertex& vertex : vertices)
    {
        vertex.SortEdges();
    }

    vector<vector<Edge>> faces = {};
    for (Edge edge : edges)
    {
        if (edge.visited)
        {
            continue;
        }

        vector<Edge> face = {};
        faces.push_back(face);
        Edge e = edge;
    }

    // MAIN

    return dualGraph;
}

optional<Graph> ReadGraph(istream& input)
{
    size_t vertexesCount;
    input >> vertexesCount;
    Graph graph(vertexesCount);
    Graph::Vertex v1, v2;

    while ((input >> v1) && (input >> v2))
    {
        v1--;
        v2--;
        graph.AddEdge(v1, v2);
    }

    return graph;
}
