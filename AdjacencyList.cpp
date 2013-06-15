#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(void)
{
}

AdjacencyList::AdjacencyList(int count) : std::vector<std::vector<Edge>>(count)
{
}

AdjacencyList::~AdjacencyList(void)
{
}