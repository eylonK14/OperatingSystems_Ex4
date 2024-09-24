#include "EulerianCycleFinder.hpp"

/**
 * @brief Tests if a given graph is Eulerian and prints the result.
 *
 * This function checks if the provided graph is Eulerian by calling the
 * isEulerian() method of the Graph class. It then prints the result:
 * - "graph is not Eulerian" if the graph is not Eulerian.
 * - "graph has a Euler path" if the graph has an Euler path.
 * - "graph has a Euler cycle" if the graph has an Euler cycle, followed by
 *   printing the Euler circuit using the printEulerCircuit() method of the
 *   Graph class.
 *
 * @param g Reference to the Graph object to be tested.
 */
void testEulerian(Graph &g)
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

/**
 * @brief Entry point of the program.
 *
 * This function parses command-line arguments to initialize the number of edges, vertices, and seed for random graph generation.
 * It then generates a random graph based on these parameters, prints the graph, and tests if the graph is Eulerian.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 *
 * Command-line arguments:
 * -e <edges>    : Number of edges in the graph.
 * -v <vertices> : Number of vertices in the graph.
 * -s <seed>     : Seed for random number generation.
 *
 * If the required arguments are not provided, the program will print the usage information and exit with status 1.
 *
 * @return int Exit status of the program.
 */
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

    if (v * v - 1 < e)
    {
        std::cerr << "Invalid number of edges for given amount of vertexes" << std::endl;
        std::exit(1);
    }

    Graph g = Graph::generateRandomGraph(v, e, seed);
    g.printGraph();
    testEulerian(g);
    std::cout << std::endl;
    std::exit(0);
}
