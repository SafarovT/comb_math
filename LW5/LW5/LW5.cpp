#include <iostream>
#include "BipGraph.h"

int main()
{
    BipGraph g(4, 4);
    g.AddEdge(1, 2);
    g.AddEdge(1, 3);
    g.AddEdge(2, 1);
    g.AddEdge(3, 2);
    g.AddEdge(4, 2);
    g.AddEdge(4, 4);

    std::cout << "Size of maximum matching is " << g.HopcroftKarp();
    return 0;
}
