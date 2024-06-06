#pragma once
#include <list>

class BipGraph
{
public:
	BipGraph(int m, int n);
	void AddEdge(int u, int v);

	bool AugPathBFS();
	bool AddAugPathDFS(int u);
	int HopcroftKarp();

private:
	int m, n;
	std::list<int>* adj;
	int *pairU, *pairV, *dist;
};