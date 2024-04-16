#include "utils.h"
#include <fstream>
#include <algorithm>

namespace
{
	using namespace std;

    void FindCycleDFS(Graph const& graph, vector<bool>& used, size_t const& vertex, size_t const& lastVertex)
    {
        cout << "In with vertex " << vertex << endl;
        if (used[vertex])
        {
            cout << "Cycle found" << endl;
            exit(0);
        }
        used[vertex] = true;
        for (auto& vertex2 : graph.GetAdj(vertex))
        {
            if (vertex2 != vertex && vertex2 != lastVertex)
            {
                FindCycleDFS(graph, used, vertex2, vertex);
            }
        }
    }

    optional<int> FindUnusedNeighbour(vector<Graph::Vertex> const& adj, vector<bool>& used)
    {
        for (size_t i = 0; i < adj.size(); i++)
        {
            if (!used[i]) {
                return i;
            }
        }
        return nullopt;
    }

    void FindCycles(Graph const& graph)
    {
        auto size = graph.GetSize();
        vector<bool> used;
        used.assign(size, false);

        for (size_t i = 0; i < size; i++)
        {
            auto unusedVertex = FindUnusedNeighbour(graph.GetAdj(i), used);
            if (unusedVertex)
            {
                FindCycleDFS(graph, used, *unusedVertex, i);
            }
        }
    }
}

Graph GetDualGraph(Graph const& graph)
{
    Graph dualGraph;
    FindCycles(graph);

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
