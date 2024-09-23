#pragma once

#include <bits/stdc++.h>

// A class that represents a directed graph
class Graph
{
	int V; // No. of vertices
	std::list<int> *adj; // A dynamic array of adjacency lists
public:
	// Constructor and destructor
	Graph(int V) {this->V = V; adj = new std::list<int>[V]; }
	~Graph() { delete [] adj; } // To avoid memory leak

	// function to add an edge to graph
	void addEdge(int, int);

	// Method to check if this graph is Eulerian or not
	int isEulerian();

	// Method to check if all non-zero degree vertices are connected
	bool isConnected();

	// Function to do DFS starting from v. Used in isConnected();
	void DFSUtil(int, int[]);

	int degree(int);

	int inDegree(int);

	int outDegree(int);

	void printGraph();

	void printEulerCircuit();

	static Graph generateRandomGraph(int, int, int);
};
