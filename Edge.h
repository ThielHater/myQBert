#pragma once

class Edge
{
	public:		
		Edge(int arg_target, double arg_weight);
		~Edge(void);
		int target;
		double weight;
};