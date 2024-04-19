#include "utils.h"
#include <fstream>

namespace
{
	using namespace std;
}

Graph GetDualGraph(GraphStruct& graph)
{
    Graph dualGraph;
    
    // MAIN

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

    for (auto& face : faces)
    {
        cout << "[";
        for (auto& e : face)
        {
            cout << e->from->ToString() << ", ";
        }
        cout << "]" << endl;
    }

    // MAIN

    return dualGraph;
}
