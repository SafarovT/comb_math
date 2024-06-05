#include "Graph.h"
#include <fstream>
#include <stdexcept>
#include <set>

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

Graph::Graph(GraphFaces graphFaces)
    : m_faces(graphFaces)
{
}

void Graph::ToDual()
{
    GraphFaces faces = m_faces;
    m_adj.assign(faces.size(), {});
    m_merged.assign(faces.size(), {});

    vector<vector<pair<int, int>>> edges;
    for (auto& face : faces)
    {
        edges.push_back({});
        for (int i = 0; i < face.size(); i++)
        {
            auto from = face[i];
            auto to = i == face.size() - 1 ? face[0] : face[i + 1];
            edges[edges.size() - 1].push_back({ from, to });
        }
    }

    int checkingFaceNumber = 0;
    while (checkingFaceNumber < edges.size() - 1)
    {
        auto edgeToCheck = edges[checkingFaceNumber][0];
        for (int i = checkingFaceNumber + 1; i < edges.size(); i++)
        {
            for (vector<pair<int, int>>::iterator it = edges[i].begin(); it != edges[i].end();)
            {
                if ((it->first == edgeToCheck.first && it->second == edgeToCheck.second) || (it->second == edgeToCheck.first && it->first == edgeToCheck.second))
                {
                    AddEdge(checkingFaceNumber, i);
                    it = edges[i].erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        edges[checkingFaceNumber].erase(edges[checkingFaceNumber].begin());
        if (edges[checkingFaceNumber].size() == 0)
        {
            checkingFaceNumber++;
        }
    }
}

Graph::GraphFaces Graph::GetFaces() const
{
    return m_faces;
}

Graph::Graph(size_t size)
{
    m_adj.assign(size, {});
    m_merged.assign(size, false);
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
    m_merged.push_back(false);
    return GetSize() - 1;
}

bool Graph::IsStar(size_t v) const
{
    int vUniqN = 0;
    set<int> ns;
    for (auto& n : m_adj[v])
    {
        auto found = ns.find(n);
        if (found == ns.end())
        {
            ns.insert(n);
            vUniqN++;
        }
    }

    return vUniqN == GetSize() - 1 - m_mergedCount;
}

size_t Graph::MergeVertex(size_t v1, size_t v2)
{
    m_mergedCount++;
    for (auto& n : m_adj[v2])
    {
        for (auto& nAdj : m_adj[n])
        {
            if (nAdj == v2)
            {
                nAdj = v1;
                m_adj[v1].push_back(n);
            }
        }
    }
    m_adj[v2] = {};
    m_merged[v2] = true;
    return v1;
}

bool Graph::IsMerged(size_t v) const
{
    return m_merged[v];
}
