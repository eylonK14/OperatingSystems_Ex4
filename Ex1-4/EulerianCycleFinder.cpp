#include "EulerianCycleFinder.hpp"

/**
 * @brief Adds an edge to the graph.
 *
 * This function adds a directed edge from vertex v to vertex w in the adjacency list.
 *
 * @param v The starting vertex of the edge.
 * @param w The ending vertex of the edge.
 */
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

/**
 * @brief Computes the degree of a vertex in the graph.
 *
 * The degree of a vertex is defined as the sum of its out-degree and in-degree.
 *
 * @param v The vertex for which the degree is to be computed.
 * @return The degree of the vertex.
 */
int Graph::degree(int v)
{
    return outDegree(v) + inDegree(v);
}

/**
 * @brief Calculates the in-degree of a given vertex in the graph.
 *
 * The in-degree of a vertex is the number of edges directed towards that vertex.
 *
 * @param v The vertex for which the in-degree is to be calculated.
 * @return The in-degree of the vertex.
 */
int Graph::inDegree(int v)
{
    int in_going_edges = 0;
    for (int i = 0; i < this->V; i++)
        for (std::list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++)
            if (*it == v)
                in_going_edges++;
    return in_going_edges;
}

/**
 * @brief Computes the out-degree of a given vertex in the graph.
 *
 * The out-degree of a vertex is the number of edges leaving that vertex.
 *
 * @param v The vertex for which the out-degree is to be computed.
 * @return The out-degree of the specified vertex.
 */
int Graph::outDegree(int v)
{
    return adj[v].size();
}

/**
 * @brief Prints the adjacency list representation of the graph.
 *
 * This function iterates through each vertex of the graph and prints
 * its adjacency list. Each vertex and its corresponding adjacent vertices
 * are printed in the format:
 *
 * vertex: adjacent_vertex1 adjacent_vertex2 ...
 *
 * Example output for a graph with 3 vertices:
 * 0: 1 2
 * 1: 0 2
 * 2: 0 1
 *
 * @note This function assumes that the graph is represented using an
 * adjacency list stored in the member variable `adj`.
 */
void Graph::printGraph()
{
    for (int i = 0; i < this->V; i++)
    {
        std::cout << i << ": ";
        std::list<int>::iterator it;
        for (it = adj[i].begin(); it != adj[i].end(); it++)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * @brief Utility function for Depth First Search (DFS) traversal of the graph.
 *
 * This function is used to traverse the graph starting from a given vertex `v`.
 * It marks the visited vertices and recursively visits all the vertices that
 * are adjacent to the current vertex and have not been fully visited.
 *
 * @param v The starting vertex for the DFS traversal.
 * @param visited An array to keep track of the visited vertices. Each element
 *                in the array represents the number of times a vertex has been visited.
 */
void Graph::DFSUtil(int v, int visited[])
{
    visited[v]++;

    std::list<int>::iterator it;
    for (it = adj[v].begin(); it != adj[v].end(); ++it)
        if (visited[*it] < degree(*it))
            DFSUtil(*it, visited);
}

/**
 * @brief Checks if the graph is connected.
 *
 * This function determines if the graph is connected by performing the following steps:
 * 1. Initializes a visited array to keep track of visited vertices.
 * 2. Finds a vertex with a non-zero degree to start the DFS traversal.
 * 3. If all vertices have zero degree, the graph is considered connected.
 * 4. Performs a Depth-First Search (DFS) starting from the found vertex.
 * 5. After the DFS traversal, checks if there are any unvisited vertices with a non-zero degree.
 *
 * @return true if the graph is connected, false otherwise.
 */
bool Graph::isConnected()
{

    int visited[V];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = 0;

    for (i = 0; i < V; i++)
        if (degree(i) != 0)
            break;

    if (i == V)
        return true;

    DFSUtil(i, visited);

    for (i = 0; i < V; i++)
        if (visited[i] == 0 && degree(i) > 0)
            return false;

    return true;
}

/**
 * @brief Determines if the graph is Eulerian.
 *
 * This function checks if the graph is Eulerian by performing the following steps:
 * 1. Checks if the graph is connected. If not, returns 0.
 * 2. Counts the number of vertices with an odd degree.
 * 3. Ensures that the in-degree and out-degree of each vertex are equal.
 * 4. If more than two vertices have an odd degree, returns 0.
 *
 * @return
 * - 0 if the graph is not Eulerian.
 * - 1 if the graph has an Eulerian path (semi-Eulerian).
 * - 2 if the graph has an Eulerian cycle.
 */
int Graph::isEulerian()
{

    if (isConnected() == false)
        return 0;

    int odd = 0;
    for (int i = 0; i < V; i++)
    {
        odd += degree(i) % 2;
        if (inDegree(i) != outDegree(i))
            return 0;
    }

    if (odd > 2)
        return 0;

    return odd ? 1 : 2;
    ;
}

/**
 * @brief Prints the Eulerian circuit of the graph.
 *
 * This function finds and prints the Eulerian circuit of the graph using
 * Hierholzer's algorithm. It starts from vertex 0 and traverses the graph
 * using a stack to keep track of the current path and a vector to store
 * the final circuit. The function assumes that the graph is represented
 * using an adjacency list stored in the member variable `adj`.
 *
 * The function performs the following steps:
 * 1. Initializes a stack to keep track of the current path and a vector
 *    to store the final circuit.
 * 2. Pushes the starting vertex (0) onto the stack.
 * 3. While the stack is not empty, it performs the following:
 *    - Gets the current vertex from the top of the stack.
 *    - If the current vertex has adjacent vertices, it pushes the next
 *      adjacent vertex onto the stack and removes it from the adjacency list.
 *    - If the current vertex has no adjacent vertices, it adds the current
 *      vertex to the circuit and pops it from the stack.
 * 4. Prints the vertices in the circuit in reverse order, separated by " -> ".
 *
 * @note The function assumes that the graph has an Eulerian circuit.
 */
void Graph::printEulerCircuit()
{
    if (adj == nullptr)
        return;

    std::stack<int> curr_path;
    std::vector<int> circuit;

    curr_path.push(0);

    while (!curr_path.empty())
    {
        int curr_v = curr_path.top();

        if (!adj[curr_v].empty())
        {
            int next_v = adj[curr_v].back();
            adj[curr_v].pop_back();
            curr_path.push(next_v);
        }
        else
        {
            circuit.push_back(curr_v);
            curr_path.pop();
        }
    }

    for (int i = circuit.size() - 1; i >= 0; i--)
    {
        std::cout << circuit[i];
        if (i > 0)
        {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Generates a random graph with a specified number of vertices and edges.
 *
 * This function creates a random graph with `v` vertices and `e` edges using the provided seed for random number generation.
 * It ensures that there are no self-loops and no duplicate edges between any two vertices.
 *
 * @param v The number of vertices in the graph.
 * @param e The number of edges to be added to the graph.
 * @param seed The seed for the random number generator to ensure reproducibility.
 * @return A randomly generated graph with `v` vertices and `e` edges.
 */
Graph Graph::generateRandomGraph(int v, int e, int seed)
{
    std::srand(seed);
    Graph g(v);
    for (int i = 0; i < e; i++)
    {
        int src = std::rand() % v;
        int dst = std::rand() % v;
        if (src == dst)
        {
            i--;
            continue;
        }

        bool flag = false;
        std::list<int>::iterator it;
        for (it = g.adj[src].begin(); it != g.adj[src].end(); it++)
            if (*it == dst)
                flag = true;
        if (flag)
        {
            i--;
            continue;
        }

        for (it = g.adj[dst].begin(); it != g.adj[dst].end(); it++)
            if (*it == src)
                flag = true;
        if (flag)
        {
            i--;
            continue;
        }

        g.addEdge(src, dst);
    }
    return g;
}
