#include "AdjacencyList.h"

AdjacencyList::AdjacencyList() : std::vector<std::vector<Edge>>(31)
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