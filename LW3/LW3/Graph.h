#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Graph
{
public:
	using Vertex = size_t;
	using Face = std::vector<Vertex>;
	using GraphFaces = std::vector<Face>;

	Graph() = default;
	Graph(GraphFaces graphFaces);
	Graph(size_t size);
	Graph(std::string const& fileName);
	Graph(std::istream& input);

	size_t GetSize() const;
	std::vector<Vertex> GetAdj(size_t v) const;

	void AddEdge(size_t v1, size_t v2);
	size_t AddVertex();
	void PrintGraph(std::ostream& output) const;
	size_t MergeVertex(size_t v1, size_t v2);
	bool IsMerged(size_t v) const;
	bool IsStar(size_t v) const;
	void ToDual();
	GraphFaces GetFaces() const;

private:
	std::vector<std::vector<Vertex>> m_adj;
	int m_mergedCount = 0;
	std::vector<bool> m_merged;
	GraphFaces m_faces;
};

