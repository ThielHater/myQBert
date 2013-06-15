#pragma once
#include "Node.h"

class Edge
{
	public:		
		Edge(Node arg_target, double arg_weight);
		~Edge(void);
		Node target;
		double weight;
};