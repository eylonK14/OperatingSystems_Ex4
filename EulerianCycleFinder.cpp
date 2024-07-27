#include "EulerianCycleFinder.hpp"

EulerianCycleFinder::EulerianCycleFinder(const EdgeVector &edges)
{
    ConstructMapping(edges);
}

void EulerianCycleFinder::printEulerianCycle()
{
    if ((*this).IsEulerianCycle())
    {
        std::vector<int> eulerianCycle;
        (*this).FindEulerianCycle(0, eulerianCycle);

        std::cout << "Start --> ";
        for (const auto &vertex : eulerianCycle)
        {
            std::cout << vertex << " --> ";
        }
        std::cout << "End" << std::endl;
    }
    else
    {
        std::cout << "Graph has no Eulerian Cycle!" << std::endl;
    }
}

bool EulerianCycleFinder::IsEulerianCycle() const
{
    if (m_vertexMap.empty())
    {
        return false;
    }
    size_t edgesCount = 0;

    int oddDegreeCount = 0;
    for (const auto &vertex : m_vertexMap)
    {
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
    int startingVertex,
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

        if (m_vertexMap.find(src) == m_vertexMap.end())
            m_vertexMap[src] = Vertex{};

        if (m_vertexMap.find(dest) == m_vertexMap.end())
            m_vertexMap[dest] = Vertex{};

        m_vertexMap[src].outgoingEdges.insert(dest);
        m_vertexMap[dest].ingoingEdges.insert(src);
    }
}

void EulerianCycleFinder::DFS(int src, std::vector<int> &eulerianCycle)
{
    Vertex &currVertex{m_vertexMap[src]};

    while (!currVertex.outgoingEdges.empty())
    {
        int dest{*currVertex.outgoingEdges.begin()};
        currVertex.outgoingEdges.erase(dest);

        Vertex &destVertex{m_vertexMap[dest]};
        destVertex.ingoingEdges.erase(src);

        DFS(dest, eulerianCycle);
    }

    eulerianCycle.insert(eulerianCycle.begin(), src);
}