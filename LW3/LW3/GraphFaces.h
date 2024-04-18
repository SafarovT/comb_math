#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <memory>
#include <string>

class Point2D
{
public:
	Point2D(int x, int y)
		: x(x)
		, y(y)
	{}

	int x, y;
};

class Edge;

class Vertex
{
public:
	int index;
	Point2D point;
	std::vector<Edge*> outboundEdges;

	Vertex(int index, Point2D point);

	bool operator==(const Vertex& vertex) const;

	void AddEdge(Edge* edge);

	void SortEdges();

	std::string ToString() const;
};

class Edge
{
public:
	Vertex* from;
	Vertex* to;
	double angle;
	bool visited = false;
	Edge* next = nullptr;
	Edge* reverse = nullptr;

	Edge(Vertex* fromD, Vertex* toD);

	bool operator==(const Edge& edge) const;

	bool operator!=(const Edge& edge) const;

	Vertex GetFrom();

	Vertex GetTo();

	void SetNextEdge(Edge* edge);

	void SetReverseEdge(Edge* edge);

	std::string ToString() const;
};
