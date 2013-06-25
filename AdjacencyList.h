#pragma once
#include <vector>
#include "Edge.h"

class AdjacencyList : public std::vector<std::vector<Edge>>
{
	public:
		AdjacencyList(int count);
		//void add(int ArgEdgeNum, int ArgNodeNum, Cube* ArgCube);
};