#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/**
 * @class EulerianCycleFinder
 * @brief Class for finding Eulerian cycles in a graph.
 *
 * The EulerianCycleFinder class provides functionality to find Eulerian cycles in a graph.
 * It takes a vector of edges as input and can print the Eulerian cycle if one exists.
 */
class EulerianCycleFinder
{
public:
    using EdgeVector = std::vector<std::vector<int>>;

    /**
     * @brief Constructs an EulerianCycleFinder object with the given edges.
     * @param edges The vector of edges representing the graph.
     */
    explicit EulerianCycleFinder(const EdgeVector &edges);

    /**
     * @brief Prints the Eulerian cycle if one exists.
     */
    void printEulerianCycle();

private:
    /**
     * @struct Vertex
     * @brief Represents a vertex in the graph.
     */
    struct Vertex
    {
        std::unordered_set<int> outgoingEdges; /**< The set of outgoing edges from the vertex. */
        std::unordered_set<int> ingoingEdges;  /**< The set of ingoing edges to the vertex. */
    };

    std::unordered_map<int, Vertex> m_vertexMap; /**< The mapping of vertex IDs to Vertex objects. */

    /**
     * @brief Checks if the graph has an Eulerian cycle.
     * @return True if the graph has an Eulerian cycle, false otherwise.
     */
    bool IsEulerianCycle() const;

    /**
     * @brief Finds the Eulerian cycle in the graph starting from the given vertex.
     * @param startingVertex The starting vertex for the Eulerian cycle.
     * @param eulerianCycle The vector to store the Eulerian cycle.
     * @return True if an Eulerian cycle is found, false otherwise.
     */
    bool FindEulerianCycle(int startingVertex, std::vector<int> &eulerianCycle);

    /**
     * @brief Constructs the mapping of vertex IDs to Vertex objects.
     * @param edges The vector of edges representing the graph.
     */
    void ConstructMapping(const EdgeVector &edges);

    /**
     * @brief Performs a depth-first search to find the Eulerian cycle.
     * @param src The source vertex for the depth-first search.
     * @param eulerianCycle The vector to store the Eulerian cycle.
     */
    void DFS(int src, std::vector<int> &eulerianCycle);
};