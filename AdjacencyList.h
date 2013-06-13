#pragma once
#include "Node.h"
#include <vector>

class AdjacencyList 
{
	public:
		AdjacencyList(int count);
		~AdjacencyList(void);
		std::vector<std::vector<Node>> adj;
};