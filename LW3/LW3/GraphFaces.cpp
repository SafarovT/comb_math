#include "GraphFaces.h"

#include <iostream>
// VERTEX

Vertex::Vertex(int index, Point2D point)
	: index(index)
	, point(point)
{}

bool Vertex::operator==(const Vertex& vertex) const
{
	return vertex.index == this->index;
}

void Vertex::AddEdge(Edge* edge)
{
	std::cout << "adding edge for " << index << std::endl;
	outboundEdges.push_back(edge);
}

void Vertex::SortEdges()
{
	std::cout << "sorting edges for " << index << ": ";
	for (auto& el : outboundEdges)
	{
		std::cout << el->ToString() << ", ";
	}
	std::cout << std::endl;
	auto compareEdges = [](Edge* e1, Edge* e2) { return e1->angle < e2->angle; };
	std::sort(outboundEdges.begin(), outboundEdges.end(), compareEdges);

	if (outboundEdges.size() == 0) return;
	auto prev = outboundEdges[outboundEdges.size() - 1];
	for (auto& edge : outboundEdges)
	{
		edge->SetNextEdge(prev);
		prev = edge;
	}
}

std::string Vertex::ToString() const
{
	return std::to_string(index);
}

// EDGE

Edge::Edge(Vertex* fromD, Vertex* toD)
	: from(fromD)
	, to(toD)
{
	angle = std::atan2(to->point.y - from->point.y, to->point.x - from->point.x);
	from->AddEdge(this);
}

bool Edge::operator==(const Edge& edge) const
{
	return (this->from == edge.from) && (this->to == edge.to);
}

bool Edge::operator!=(const Edge& edge) const
{
	return !(*this == edge);
}

Vertex Edge::GetFrom()
{
	return *from;
}

Vertex Edge::GetTo()
{
	return *to;
}

void Edge::SetNextEdge(Edge* edge)
{
	next = edge;
}

void Edge::SetReverseEdge(Edge* edge)
{
	reverse = edge;
}

std::string Edge::ToString() const
{
	return "{" + from->ToString() + "} -> {" + to->ToString() + "}";
}