#include "tree.h"
#include <fstream>
#include <vector>

namespace
{
	using namespace std;

    using GraphVertex = int;
    using Graph = vector<vector<GraphVertex>>;

    Graph graph, graphTransposed;
    vector<bool> used;
    vector<GraphVertex> order, component;

    bool OpenFile(ifstream& inputFile, string filePath)
    {
        inputFile.open(filePath);

        if (!inputFile.is_open()) {
            cout << "Failed to open file for reading \n";

            return false;
        }

        return true;
    }

    void DepthFirstSearch(GraphVertex& vertex)
    {
        used[vertex] = true;
        for (size_t i = 0; i < graph[vertex].size(); i++)
        {
            if (!used[graph[vertex][i]])
            {
                DepthFirstSearch(graph[vertex][i]);
            }
        }

        order.push_back(vertex);
    }

    void DepthFirstSearchInTransposedGraph(GraphVertex& vertex)
    {
        used[vertex] = true;
        component.push_back(vertex);
        for (size_t i = 0; i < graphTransposed[vertex].size(); i++)
        {
            if (!used[graphTransposed[vertex][i]])
            {
                DepthFirstSearchInTransposedGraph(graphTransposed[vertex][i]);
            }
        }
    }

    vector<vector<int>> transposingGraph(vector<vector<int>>& G)
    {
        int n = G.size();
        vector<vector<int>> GT(n);

        vector<int> count(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < G[i].size(); j++)
                count[G[i][j]]++;

        for (int i = 0; i < n; i++)
            GT[i].reserve(count[i]);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < G[i].size(); j++)
                GT[G[i][j]].push_back(i);

        return GT;
    }
}

void FindStrongComponents(istream& inputFile)
{
    size_t vertexesCount;
    GraphVertex fromVertex, toVertex;

    inputFile >> vertexesCount;
    graph.assign(vertexesCount, {});
    graphTransposed.assign(vertexesCount, {});
    order = {};
    component = {};
    while ((inputFile >> fromVertex) && (inputFile >> toVertex))
    {
        fromVertex--;
        toVertex--;
        graph[fromVertex].push_back(toVertex);
        // graphTransposed[toVertex].push_back(fromVertex);
    }
    graphTransposed = transposingGraph(graph);

    used.assign(vertexesCount, false);
    for (GraphVertex vertex = 0; vertex < vertexesCount; vertex++)
    {
        if (!used[vertex])
        {
            DepthFirstSearch(vertex);
        }
    }

    used.assign(vertexesCount, false);
    for (GraphVertex i = 0; i < vertexesCount; i++)
    {
        GraphVertex vertex = order[vertexesCount - 1 - i];
        if (!used[vertex]) {
            DepthFirstSearchInTransposedGraph(vertex);
            for (auto const& componentElement : component)
            {
                cout << componentElement + 1 << " ";
            }
            cout << endl;
            component.clear();
        }
    }
}

void FindStrongComponents(string const& fileName)
{
    ifstream inputFile;
    if (OpenFile(inputFile, fileName))
    {
        FindStrongComponents(inputFile);
    }
}