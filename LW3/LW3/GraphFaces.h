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
	std::vector<Edge> outboundEdges;

	Vertex(int index, Point2D point)
		: index(index)
		, point(point)
	{}

	void AddEdge(Edge& edge)
	{
		outboundEdges.push_back(edge);
	}

	void SortEdges()
	{
		auto compareEdges = [](Edge const& e1, Edge const& e2) { return e1.angle < e2.angle; };
		std::sort(outboundEdges.begin(), outboundEdges.end(), compareEdges);

		if (outboundEdges.size() == 0) return;
		Edge prev = outboundEdges[outboundEdges.size() - 1];
		for (Edge edge : outboundEdges)
		{
			edge.SetNextEdge(prev);
			prev = edge;
		}
	}

	std::string ToString() const
	{
		return std::to_string(index);
	}
};

class Edge
{
public:
	Vertex from, to;
	float angle;
	bool visited = false;
	std::shared_ptr<Edge> next = nullptr;
	std::shared_ptr<Edge> reverse = nullptr;

	Edge(Vertex const& fromD, Vertex const& toD)
		: from(fromD)
		, to(toD)
	{
		angle = std::atan2(to.point.y - from.point.y, to.point.x - from.point.x);
		from.AddEdge(*this);
	}

	Vertex GetFrom()
	{
		return from;
	}

	Vertex GetTo()
	{
		return to;
	}

	void SetNextEdge(Edge const& edge)
	{
		next = std::make_shared<Edge>(edge);
	}

	void SetReverseEdge(Edge const& edge)
	{
		reverse = std::make_shared<Edge>(edge);
	}

	std::string ToString() const
	{
		return "{" + from.ToString() + "} -> {" + to.ToString() + "}";
	}
};
