#pragma once

#include <bits/stdc++.h>

/**
 * @class Graph
 * @brief A class to represent a graph and find Eulerian cycles.
 *
 * This class provides functionalities to create a graph, add edges,
 * check if the graph is Eulerian, and print the Eulerian circuit.
 *
 * @var V Number of vertices in the graph.
 * @var adj Adjacency list representation of the graph.
 *
 * @fn Graph(int V)
 * @brief Constructor to initialize the graph with V vertices.
 * @param V Number of vertices.
 *
 * @fn ~Graph()
 * @brief Destructor to clean up the adjacency list.
 *
 * @fn void addEdge(int u, int v)
 * @brief Adds an edge to the graph.
 * @param u The starting vertex of the edge.
 * @param v The ending vertex of the edge.
 *
 * @fn int isEulerian()
 * @brief Checks if the graph is Eulerian.
 * @return 0 if the graph is not Eulerian, 1 if it has an Eulerian path, 2 if it has an Eulerian circuit.
 *
 * @fn bool isConnected()
 * @brief Checks if the graph is connected.
 * @return true if the graph is connected, false otherwise.
 *
 * @fn void DFSUtil(int v, int visited[])
 * @brief A utility function for depth-first search.
 * @param v The vertex to start the DFS from.
 * @param visited Array to keep track of visited vertices.
 *
 * @fn int degree(int v)
 * @brief Calculates the degree of a vertex.
 * @param v The vertex whose degree is to be calculated.
 * @return The degree of the vertex.
 *
 * @fn int inDegree(int v)
 * @brief Calculates the in-degree of a vertex.
 * @param v The vertex whose in-degree is to be calculated.
 * @return The in-degree of the vertex.
 *
 * @fn int outDegree(int v)
 * @brief Calculates the out-degree of a vertex.
 * @param v The vertex whose out-degree is to be calculated.
 * @return The out-degree of the vertex.
 *
 * @fn void printGraph()
 * @brief Prints the adjacency list representation of the graph.
 *
 * @fn void printEulerCircuit()
 * @brief Prints the Eulerian circuit of the graph.
 *
 * @fn static Graph generateRandomGraph(int V, int E, int seed)
 * @brief Generates a random graph with V vertices and E edges.
 * @param V Number of vertices.
 * @param E Number of edges.
 * @param seed Seed for random number generation.
 * @return A randomly generated graph.
 *
 * @brief A class to represent a directed graph using adjacency list representation.
 *
 * The Graph class provides functionalities to add edges, check if the graph is Eulerian,
 * check connectivity, perform depth-first search, calculate degrees, and print the graph
 * and Eulerian circuit. It also includes a static method to generate a random graph.
 */
class Graph
{
    int V;
    std::list<int> *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new std::list<int>[V];
    }
    ~Graph() { delete[] adj; }

    void addEdge(int, int);

    int isEulerian();

    bool isConnected();

    void DFSUtil(int, int[]);

    int degree(int);

    int inDegree(int);

    int outDegree(int);

    void printGraph();

    void printEulerCircuit();

    static Graph generateRandomGraph(int, int, int);
};
