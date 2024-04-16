#include "Graph.h"
#include <fstream>
#include <stdexcept>

namespace
{
	using namespace std;

    bool OpenFile(ifstream& inputFile, string filePath)
    {
        inputFile.open(filePath);

        if (!inputFile.is_open()) {
            cout << "Failed to open file for reading \n";

            return false;
        }

        return true;
    }

    Graph ReadGraph(istream& input)
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
}

Graph::Graph(size_t size)
{
    m_adj.assign(size, {});
}

Graph::Graph(string const& fileName)
{
	ifstream inputFile;
	if (!OpenFile(inputFile, fileName))
	{
        throw new exception("Unable to open file");
	}

    *this = ReadGraph(inputFile);
}

Graph::Graph(istream& input)
{
    *this = ReadGraph(input);
}

void Graph::AddEdge(size_t v1, size_t v2)
{
    auto size = GetSize();
    if (v1 >= size || v2 >= size)
    {
        return;
    }
    m_adj[v1].push_back(v2);
    m_adj[v2].push_back(v1);
}

size_t Graph::GetSize() const
{
    return m_adj.size();
}

vector<Graph::Vertex> Graph::GetAdj(size_t v) const
{
    return m_adj[v];
}

void Graph::PrintGraph(std::ostream& output) const
{
    auto size = GetSize();
    output << "[";
    for (size_t i = 0; i < size; i++)
    {
        for (auto const& j : m_adj[i])
        {
            output << "(" << i << "," << j << "), ";
        }
    }
    output << "]" << endl;
}

size_t Graph::AddVertex()
{
    m_adj.push_back({});
    return GetSize() - 1;
}
