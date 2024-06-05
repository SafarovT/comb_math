#pragma once
#include <iostream>
#include <optional>
#include "GraphFaces.h"
#include "Graph.h"

Graph::GraphFaces GetGraphFaces(GraphStruct& graph);
Graph GetDualGraph(Graph::GraphFaces& faces);
std::vector<int> ColorGraph(Graph& graph);