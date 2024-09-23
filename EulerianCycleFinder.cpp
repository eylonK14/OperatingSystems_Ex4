#include "EulerianCycleFinder.hpp"

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	// adj[w].push_back(v); // Note: the graph is undirected
}

int Graph::degree(int v)
{
	return outDegree(v) + inDegree(v);
}

int Graph::inDegree(int v)
{
	int in_going_edges = 0;
	for (int i = 0; i < this->V; i++)
		for (std::list<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++)
			if (*it == v)
				in_going_edges++;
	return in_going_edges;
}

int Graph::outDegree(int v)
{
	return adj[v].size();
}

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

void Graph::DFSUtil(int v, int visited[])
{
	// Mark the current node as visited and print it
	visited[v]++; // = true;

	// Recur for all the vertices adjacent to this vertex
	std::list<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end(); ++it)
		if (visited[*it] < degree(*it))
			DFSUtil(*it, visited);
}

// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool Graph::isConnected()
{
	// Mark all the vertices as not visited
	int visited[V];
	int i;
	for (i = 0; i < V; i++)
		visited[i] = 0;

	// Find a vertex with non-zero degree
	for (i = 0; i < V; i++)
		if (degree(i) != 0)
			break;

	// If there are no edges in the graph, return true
	if (i == V)
		return true;

	// Start DFS traversal from a vertex with non-zero degree
	DFSUtil(i, visited);

	// Check if all non-zero degree vertices are visited
	for (i = 0; i < V; i++)
	if (visited[i] == 0 && degree(i) > 0)
			return false;

	return true;
}

/* The function returns one of the following values
0 --> If graph is not Eulerian
1 --> If graph has an Euler path (Semi-Eulerian)
2 --> If graph has an Euler Circuit (Eulerian) */
int Graph::isEulerian()
{
	// Check if all non-zero degree vertices are connected
	if (isConnected() == false)
		return 0;

	// Count vertices with odd degree
	int odd = 0;
	for (int i = 0; i < V; i++)
	{
		odd += degree(i) % 2;
		if (inDegree(i) != outDegree(i))
			return 0;
	}

	// If count is more than 2, then graph is not Eulerian
	if (odd > 2)
		return 0;

	// If odd count is 2, then semi-eulerian.
	// If odd count is 0, then eulerian
	// Note that odd count can never be 1 for undirected graph
	return odd ? 1 : 2;;
}

void Graph::printEulerCircuit()
{
	if (adj == nullptr) return;

    std::stack<int> curr_path;
    std::vector<int> circuit;
    
    curr_path.push(0);

    while (!curr_path.empty()) {
        int curr_v = curr_path.top();

        if (!adj[curr_v].empty()) {
            int next_v = adj[curr_v].back();
            adj[curr_v].pop_back();
            curr_path.push(next_v);
        } else {
            circuit.push_back(curr_v);
            curr_path.pop();
        }
    }

    for (int i = circuit.size() - 1; i >= 0; i--) {
        std::cout << circuit[i];
        if (i > 0) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

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

		// if the edge already exists, skip it
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

		// if the opposite edge already exists, skip it
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
