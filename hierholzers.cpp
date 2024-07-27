// A C++ program to print Eulerian circuit in given
// directed graph using Hierholzer algorithm

#include <iostream>
#include <bits/stdc++.h>
#include <unordered_map>
#include <stack>

#include "graph.hpp"

void printCircuit(Graph graph)
{
	auto adj = graph.getAdjList();
	// adj represents the adjacency list of
	// the directed graph
	// edge_count represents the number of edges
	// emerging from a vertex
	std::unordered_map<int, int> edge_count;

	for (int i = 0; i < adj.size(); i++)
	{
		// find the count of edges to keep track
		// of unused edges
		edge_count[i] = adj[i].size();
	}

	if (!adj.size())
		return; // empty graph

	// Maintain a stack to keep vertices
	std::stack<int> curr_path;

	// vector to store final circuit
	std::vector<int> circuit;

	// start from any vertex
	curr_path.push(0);
	int curr_v = 0; // Current vertex

	while (!curr_path.empty())
	{
		// If there's remaining edge
		if (edge_count[curr_v])
		{
			// Push the vertex
			curr_path.push(curr_v);

			// Find the next vertex using an edge
			int next_v = adj[curr_v].back();

			// and remove that edge
			edge_count[curr_v]--;
			adj[curr_v].pop_back();

			// Move to next vertex
			curr_v = next_v;
		}

		// back-track to find remaining circuit
		else
		{
			circuit.push_back(curr_v);

			// Back-tracking
			curr_v = curr_path.top();
			curr_path.pop();
		}
	}

	// we've got the circuit, now print it in reverse
	for (int i = circuit.size() - 1; i >= 0; i--)
	{
		std::cout << circuit[i];
		if (i)
			std::cout << " -> ";
	}
}

// Driver program to check the above function
int main()
{
	// std::vector<std::vector<int>> adj1, adj2;
	Graph graph1(3), graph2(7);

	graph1.addEdge(0, 1);
	graph1.addEdge(1, 2);
	graph1.addEdge(2, 0);

	graph2.addEdge(0, 1);
	graph2.addEdge(0, 6);
	graph2.addEdge(1, 2);
	graph2.addEdge(2, 0);
	graph2.addEdge(2, 3);
	graph2.addEdge(3, 4);
	graph2.addEdge(4, 2);
	graph2.addEdge(4, 5);
	graph2.addEdge(5, 0);
	graph2.addEdge(6, 4);

	printCircuit(graph1);
	std::cout << std::endl;
	printCircuit(graph2);
	std::cout << std::endl;

	// Input Graph 1
	// adj1.resize(3);

	// Build the edges
	// adj1[0].push_back(1);
	// adj1[1].push_back(2);
	// adj1[2].push_back(0);
	// printCircuit(adj1);
	// std::cout << std::endl;

	// Input Graph 2
	// adj2.resize(7);
	// adj2[0].push_back(1);
	// adj2[0].push_back(6);
	// adj2[1].push_back(2);
	// adj2[2].push_back(0);
	// adj2[2].push_back(3);
	// adj2[3].push_back(4);
	// adj2[4].push_back(2);
	// adj2[4].push_back(5);
	// adj2[5].push_back(0);
	// adj2[6].push_back(4);
	// printCircuit(adj2);

	return 0;
}
