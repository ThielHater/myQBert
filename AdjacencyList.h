#pragma once
#include "Edge.h"
#include <vector>

class AdjacencyList : public std::vector<std::vector<Edge>>
{
	public:
		AdjacencyList(void);
		AdjacencyList(int count);
		~AdjacencyList(void);
};