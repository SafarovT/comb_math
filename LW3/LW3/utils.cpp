#include "utils.h"
#include <fstream>
#include <algorithm>

namespace
{
	using namespace std;

    bool cyclesFound = false;
    vector<size_t> graphFaces = { };
    vector<size_t> faceEnds = { };

    bool IsAllUsed(vector<bool> const& used)
    {
        for (auto const& el : used)
        {
            if (!el)
            {
                return false;
            }
        }

        return true;
    }

    void FindCycleDFS(Graph const& graph, vector<bool>& used, size_t const& vertex, size_t const& lastVertex)
    {
        if (cyclesFound)
        {
            return;
        }
        // cout << "In with vertex " << lastVertex << "->" << vertex << endl;
        if (used[vertex])
        {
            // cout << "Cycle found" << endl;
            cyclesFound = IsAllUsed(used);
            graphFaces.push_back({ graphFaces.size() });
            cout << "{" << lastVertex << "," << vertex << "}" << "->";
            for (auto const& graphFace : graphFaces)
            {
               cout << graphFace << ", ";
            }
            // faceEnds[graphFaces[graphFaces.size() - 1]] = vertex;
            cout << endl;
            return;
        }
        used[vertex] = true;
        for (auto& vertex2 : graph.GetAdj(vertex))
        {
            if (vertex2 != vertex && vertex2 != lastVertex)
            {
                FindCycleDFS(graph, used, vertex2, vertex);
            }
        }

        cout << "{" << lastVertex << "," << vertex << "}" << "->";
        for (auto const& graphFace : graphFaces)
        {
            cout << graphFace << ", ";
            /*if (faceEnds[graphFace] == vertex)
            {
                faceEnds.pop_back();
            }*/
        }
        cout << endl;
    }

    optional<int> FindUnusedNeighbour(vector<Graph::Vertex> const& adj, vector<bool>& used)
    {
        for (size_t i = 0; i < adj.size(); i++)
        {
            if (!used[adj[i]])
            {
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
        
        FindCycleDFS(graph, used, 0, 0);
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
