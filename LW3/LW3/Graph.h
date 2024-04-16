#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Graph
{
public:
	using Vertex = size_t;

	Graph() = default;
	Graph(size_t size);
	Graph(std::string const& fileName);
	Graph(std::istream& input);

	size_t GetSize() const;
	std::vector<Vertex> GetAdj(size_t v) const;

	void AddEdge(size_t v1, size_t v2);
	size_t AddVertex();
	void PrintGraph(std::ostream& output) const;

private:
	std::vector<std::vector<Vertex>> m_adj;
};

