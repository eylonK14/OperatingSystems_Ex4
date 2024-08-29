// A C++ program to print Eulerian circuit in given
// directed graph using Hierholzer algorithm

#include <iostream>
#include <bits/stdc++.h>
#include <stack>

#include "EulerianCycleFinder.hpp"

EulerianCycleFinder::EdgeVector generateGraph(int v, int e, int seed)
{
	EulerianCycleFinder::EdgeVector graph;
	std::srand(seed);

	for (int i = 0; i < e; i++)
	{
		int v1 = std::rand() % v;
		int v2 = std::rand() % v;
		if (v1 == v2)
		{
			i--;
			continue;
		}
		int flag = 0;
		// if the edge already exists in the graph, ignore it
		for (auto &edge : graph)
		{
			std::cout << "edge[0]: " << edge[0] << " edge[1]: " << edge[1] << std::endl;
			if ((edge[0] == v1 && edge[1] == v2))
			{
				i--;
				flag = 1;
			}
		}
		if (flag)
			continue;

		std::cout << v1 << " -> " << v2 << std::endl;
		graph.push_back({v1, v2});
		// graph.push_back({v2, v1});
	}

	return graph;
}

// Driver program to check the above function
int main(int argc, char **argv)
{
	int opt = 0, seed = 0, v = 0, e = 0;
	if (argc < 4)
	{
		std::cerr << "Usage: " << argv[0] << " -e <edges> -v <vertices> -s <seed>" << std::endl;
		std::exit(1);
	}

	while ((opt = getopt(argc, argv, "e:v:s:")) != -1)
	{
		switch (opt)
		{
		case 'e':
			e = atoi(optarg);
			break;
		case 'v':
			v = atoi(optarg);
			break;
		case 's':
			seed = atoi(optarg);
			break;
		default:
			break;
		}
	}

	auto directedEdges = generateGraph(v, e, seed);
	EulerianCycleFinder finder(directedEdges);
	finder.printEulerianCycle();
	std::cout << std::endl;

	return 0;
}
