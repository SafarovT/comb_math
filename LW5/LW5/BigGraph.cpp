#include "BipGraph.h"
#include <queue>

BipGraph::BipGraph(int m, int n)
	: m(m)
	, n(n)
	, adj(new std::list<int>[m + 1])
{
}

void BipGraph::AddEdge(int u, int v)
{
	adj[u].push_back(v);
}

bool BipGraph::AugPathBFS()
{
	std::queue<int> q;
	for (int u = 1; u <= m; u++)
	{
		if (pairU[u] == NULL)
		{
			dist[u] = 0;
			q.push(u);
		}
		else dist[u] = INT_MAX;
	}

	dist[NULL] = INT_MAX;

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		if (dist[u] < dist[NULL])
		{
			std::list<int>::iterator i;
			for (i = adj[u].begin(); i != adj[u].end(); i++)
			{
				int v = *i;

				if (dist[pairV[v]] == INT_MAX)
				{
					dist[pairV[v]] = dist[u] + 1;
					q.push(pairV[v]);
				}
			}
		}
	}

	return dist[NULL] != INT_MAX;
}

bool BipGraph::AddAugPathDFS(int u)
{
	if (u != NULL)
	{
		std::list<int>::iterator i;
		for (i = adj[u].begin(); i != adj[u].end(); i++)
		{
			int v = *i;

			if (dist[pairV[v]] == dist[u] + 1)
			{
				if (AddAugPathDFS(pairV[v]))
				{
					pairV[v] = u;
					pairU[u] = v;
					return true;
				}
			}
		}

		dist[u] = INT_MAX;
		return false;
	}

	return true;
}

int BipGraph::HopcroftKarp()
{
	pairU = new int[m + 1];
	pairV = new int[n + 1];
	dist = new int[m + 1];

	for (int u = 0; u <= m; u++)
		pairU[u] = NULL;
	for (int v = 0; v <= n; v++)
		pairV[v] = NULL;
	int result = 0;

	while (AugPathBFS())
	{
		for (int u = 1; u <= m; u++)
		{
			if (pairU[u] == NULL && AddAugPathDFS(u))
				result++;
		}
	}
	return result;
}