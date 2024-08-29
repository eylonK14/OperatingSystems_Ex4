#include "EulerianCycleFinder.hpp"

EulerianCycleFinder::EulerianCycleFinder(const EdgeVector &edges)
{
    ConstructMapping(edges);
}

void EulerianCycleFinder::printEulerianCycle(const int v)
{
    if (this->IsEulerianCycle(v))
    {
        for (int i = 0; i < v; i++)
        {
            std::vector<int> eulerianCycle;
            this->FindEulerianCycle(i, eulerianCycle);

            std::cout << "Start --> ";
            for (const auto &vertex : eulerianCycle)
            {
                std::cout << vertex << " --> ";
            }
            std::cout << "End" << std::endl;
        }
    }
    else
    {
        std::cout << "Graph has no Eulerian Cycle!" << std::endl;
    }
}

bool EulerianCycleFinder::IsEulerianCycle(const int v) const
{
    if (m_vertexMap.empty() || m_vertexMap.size() != v)
    {
        return false;
    }
    size_t edgesCount = 0;

    int oddDegreeCount = 0;
    for (const auto &vertex : m_vertexMap)
    {
        if (vertex.second.outgoingEdges.empty())
            return false;
        edgesCount += vertex.second.outgoingEdges.size();
        if (vertex.second.ingoingEdges.size() !=
            vertex.second.outgoingEdges.size())
        {
            oddDegreeCount++;
        }
    }
    if (oddDegreeCount != 0 && oddDegreeCount != 2)
    {
        return false;
    }
    std::cout << "Edges Count: " << edgesCount << std::endl;
    std::cout << "Vertex Count: " << m_vertexMap.size() << std::endl;
    if (edgesCount < m_vertexMap.size())
    {
        return false;
    }

    // for (const auto &vertex : m_vertexMap)
    // {
    //     if (vertex.second.ingoingEdges.size() !=
    //         vertex.second.outgoingEdges.size())
    //     {
    //         return false;
    //     }
    // }

    return true;
}

bool EulerianCycleFinder::FindEulerianCycle(
    const int startingVertex,
    std::vector<int> &eulerianCycle)
{
    DFS(startingVertex, eulerianCycle);

    return true;
}

void EulerianCycleFinder::ConstructMapping(const EdgeVector &edges)
{
    for (const auto &edge : edges)
    {
        int src{edge.at(0)};
        int dest{edge.at(1)};

        if (!m_vertexMap.contains(src))
            m_vertexMap[src] = Vertex{};

        if (!m_vertexMap.contains(dest))
            m_vertexMap[dest] = Vertex{};

        m_vertexMap[src].outgoingEdges.insert(std::make_pair(dest, false));
        m_vertexMap[dest].ingoingEdges.insert(std::make_pair(src, false));
    }
}

void EulerianCycleFinder::DFS(const int src, std::vector<int> &eulerianCycle)
{

    while (!m_vertexMap[src].outgoingEdges.empty())
    {

        int dest = m_vertexMap[src].outgoingEdges.begin()->first;  // Get the first edge destination
        // const bool visited = m_vertexMap[src].outgoingEdges.begin()->second;
        // std::cout << dest  << ", " << visited << std::endl;

        // m_vertexMap[src].outgoingEdges.at(dest) = true;
        // m_vertexMap[dest].ingoingEdges.at(src) = true;
        std::cout << dest << std::endl;
        m_vertexMap[src].outgoingEdges.erase(dest);         // Remove the edge from src to dest
        m_vertexMap[src].ingoingEdges.erase(dest);

        m_vertexMap[dest].ingoingEdges.erase(src);          // Remove the edge from dest's ingoing edges
        m_vertexMap[dest].outgoingEdges.erase(src);
        DFS(dest, eulerianCycle);                           // Recurse with the destination vertex

    }

    eulerianCycle.insert(eulerianCycle.begin(), src);       // Add the vertex to the Eulerian cycle
}

// void EulerianCycleFinder::DFS(const int src, std::vector<int> &eulerianCycle)
// {
//     while (!m_vertexMap[src].outgoingEdges.empty())
//     {
//         int dest = *m_vertexMap[src].outgoingEdges.begin();
//
//         // Remove the edge from src to dest
//         m_vertexMap[src].outgoingEdges.erase(dest);
//
//         // Remove the reverse edge from dest to src
//         m_vertexMap[dest].ingoingEdges.erase(src);
//
//         // Continue the DFS from the destination vertex
//         DFS(dest, eulerianCycle);
//     }
//
//     // Add the vertex to the Eulerian cycle
//     eulerianCycle.push_back(src);
// }


// void EulerianCycleFinder::DFS(const int src, std::vector<int> &eulerianCycle)
// {
//     auto &[outgoingEdges, ingoingEdges]{m_vertexMap[src]};
//
//     while (!outgoingEdges.empty())
//     {
//         int dest{*outgoingEdges.begin()};
//         outgoingEdges.erase(dest);
//
//         auto &[outgoingEdges, ingoingEdges]{m_vertexMap[dest]};
//         ingoingEdges.erase(src);
//
//         DFS(dest, eulerianCycle);
//     }
//
//     eulerianCycle.insert(eulerianCycle.begin(), src);
// }

// void EulerianCycleFinder::DFS(const int src, std::vector<int> &eulerianCycle)
// {
//     auto &[outgoingEdges, ingoingEdges]{m_vertexMap[src]};
//
//     while (!outgoingEdges.empty())
//     {
//         // Use iterator to ensure we remove the exact edge being traversed
//         auto it = outgoingEdges.begin();
//         int dest = *it;
//         outgoingEdges.erase(it);
//
//         // Now remove the reverse edge from dest's ingoingEdges
//         auto &[destOutgoingEdges, destIngoingEdges]{m_vertexMap[dest]};
//         destIngoingEdges.erase(destIngoingEdges.find(src));
//
//         DFS(dest, eulerianCycle);
//     }
//
//     eulerianCycle.insert(eulerianCycle.begin(), src);
// }

// void EulerianCycleFinder::DFS(const int src, std::vector<int> &eulerianCycle)
// {
//     while (!m_vertexMap[src].empty())
//     {
//         // Get the first edge (src -> dest)
//         auto edge = m_vertexMap[src].back();
//         int dest = edge.second;
//         m_vertexMap[src].pop_back(); // Remove the edge from the src's adjacency list
//
//         // Also remove the reverse edge from the dest's adjacency list
//         removeEdge(dest, src);
//
//         DFS(dest, eulerianCycle);
//     }
//
//     eulerianCycle.push_back(src);
// }
//
// void EulerianCycleFinder::removeEdge(int src, int dest)
// {
//     auto &edges = m_vertexMap[src];
//     auto it = std::find_if(edges.begin(), edges.end(), [&](const Edge &e) {
//         return e.second == dest;
//     });
//     if (it != edges.end())
//     {
//         edges.erase(it);
//     }
// }
