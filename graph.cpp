#include "graph.hpp"

Graph::Graph(int V)
{
    this->_size = V;
    this->_adjList = std::vector<std::vector<int>>(V);
}

void Graph::addEdge(int v, int w)
{
    this->_adjList[v].push_back(w);
}

void Graph::printGraph()
{
    for (int v = 0; v < this->_size; ++v)
    {
        std::cout << "Adjacency list of vertex " << v << "\nhead";
        for (auto x : this->_adjList[v])
        {
            std::cout << " -> " << x;
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> Graph::getAdjList()
{
    return this->_adjList;
}