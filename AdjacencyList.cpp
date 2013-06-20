#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int count) : std::vector<std::vector<Edge>>(count)
{
}

AdjacencyList::~AdjacencyList(void)
{
}

/*
void AdjacencyList::add(int ArgEdgeNum, int ArgNodeNum, Cube* ArgCube)
{
	Node *n = new Node(ArgNodeNum, ArgCube);
	Edge *e = new Edge(*n, 1.0f);
	this->at(ArgEdgeNum).push_back(*e);
}
*/