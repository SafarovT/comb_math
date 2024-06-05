#include "utils.h"
#include <fstream>
#include <stack>
#include <set>

namespace
{
	using namespace std;

    int graphSize;
    vector<bool> visited;
    vector<int> colors;
    int startVertex = 0;
    int color = 0;
    bool coloredAllWithCurrColor = false;
}

Graph::GraphFaces GetGraphFaces(GraphStruct& graph)
{
    vector<Edge> edges;
    edges.resize(graph.graphAdj.size() * 2);
    for (int i = 0; i < graph.graphAdj.size(); i++)
    {
        Vertex* from = &graph.vertices[graph.graphAdj[i][0] - 1];
        Vertex* to = &graph.vertices[graph.graphAdj[i][1] - 1];
        edges[2 * i] = Edge(from, to);
        edges[2 * i + 1] = Edge(to, from);

        edges[2 * i].SetReverseEdge(&edges[2 * i + 1]);
        edges[2 * i + 1].SetReverseEdge(&edges[2 * i])
            ;
        edges[2 * i].from->AddEdge(&edges[2 * i]);
        edges[2 * i + 1].from->AddEdge(&edges[2 * i + 1]);
    }

    for (Vertex& vertex : graph.vertices)
    {
        vertex.SortEdges();
    }

    vector<vector<Edge*>> faces = {};
    for (Edge& edge : edges)
    {
        if (edge.visited)
        {
            continue;
        }

        vector<Edge*> face = {};
        Edge* e = &edge;
        do
        {
            face.push_back(e);
            e->visited = true;
            e = e->reverse->next;
        } while (*e != edge);
        faces.push_back(face);
    }

    Graph::GraphFaces facesResult;
    for (auto& face : faces)
    {
        facesResult.push_back({});
        for (auto& e : face)
        {
            facesResult[facesResult.size() - 1].push_back(e->from->index);
        }
    }

    return facesResult;
}

Graph GetDualGraph(Graph::GraphFaces& faces)
{
    Graph dualGraph(faces.size());

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
                    dualGraph.AddEdge(checkingFaceNumber, i);
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

    return dualGraph;
}

void ColorGraphRec(Graph& graph, int vertex)
{
    if (visited[vertex] || graph.IsMerged(vertex) || coloredAllWithCurrColor) return;
    visited[vertex] = true;

    bool isNeighbour = vertex == startVertex;
    for (auto& n : graph.GetAdj(vertex)) // провер€ем €вл€етс€ ли окрестность первого пор€дка
    {
        if (isNeighbour) break;
        isNeighbour = n == startVertex;
    }
    if (!isNeighbour && colors[vertex] == -1) // Ќашли окрестность второго пор€дка
    {
        colors[vertex] = color;
        startVertex = graph.MergeVertex(startVertex, vertex);
        if (graph.IsStar(startVertex)) // если звезда => закрасили последнюю этим цветов
        {
            coloredAllWithCurrColor = true;
        }
    }

    for (auto& n : graph.GetAdj(vertex))
    {
        ColorGraphRec(graph, n);
    }
}

vector<int> ColorGraph(Graph& graph)
{
    graphSize = graph.GetSize();
    visited.assign(graphSize, false);
    colors.assign(graphSize, -1);
    startVertex = 0;
    color = 0;
    coloredAllWithCurrColor = false;
    bool goNextColor = false;

    // после конца
    do
    {
        colors[startVertex] = color;
        goNextColor = false;
        coloredAllWithCurrColor = false;
        ColorGraphRec(graph, startVertex);

        bool foundStartVertex = false;
        int newStartVertex = 0;
        while (!foundStartVertex && newStartVertex < graphSize)
        {
            foundStartVertex = colors[newStartVertex] == -1;
            if (foundStartVertex) break;
            newStartVertex++;
        }
        if (foundStartVertex) // нашли вершину чтобы красить в другой цвет
        {
            startVertex = newStartVertex;
            goNextColor = true;
        }
        color++;
        visited.assign(graphSize, false);
    } while (goNextColor);

    for (int i = 0; i < graphSize; i++)
    {
        std::cout << i << ": " << colors[i] << endl;
    }
    std::cout << endl;

    return colors;
}
