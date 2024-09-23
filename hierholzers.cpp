#include "EulerianCycleFinder.hpp"

// Function to run test cases
void test(Graph &g)
{
	int res = g.isEulerian();
	if (res == 0)
		std::cout << "graph is not Eulerian" << std::endl;
    
	else if (res == 1)
		std::cout << "graph has a Euler path" << std::endl;
	else
	{
		std::cout << "graph has a Euler cycle: " << std::endl;
		g.printEulerCircuit();
	}
}

// Driver program to test above function
int main(const int argc, char **argv)
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

	Graph g = Graph::generateRandomGraph(v, e, seed);
	g.printGraph();
	test(g);
	std::cout << std::endl;
	std::exit(0);
}
