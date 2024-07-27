#pragma once

#include <iostream>
#include <vector>

/**
 * @class Graph
 * @brief Represents a graph data structure.
 *
 * This class provides methods to create and manipulate a graph.
 */
class Graph
{
public:
    /**
     * @brief Constructs a graph with the specified number of vertices.
     *
     * @param V The number of vertices in the graph.
     */
    Graph(int V);

    /**
     * @brief Adds an edge between two vertices in the graph.
     *
     * @param v The source vertex.
     * @param w The destination vertex.
     */
    void addEdge(int v, int w);

    /**
     * @brief Prints the adjacency list representation of the graph.
     */
    void printGraph();

    /**
     * @brief Returns the adjacency list representation of the graph.
     *
     * @return The adjacency list.
     */
    std::vector<std::vector<int>> getAdjList();

private:
    int _size;                              /**< The number of vertices in the graph. */
    std::vector<std::vector<int>> _adjList; /**< The adjacency list representation of the graph. */
};
