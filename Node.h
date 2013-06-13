#pragma once
#include <vector>
#include <string>
#include <list>
#include <limits> 
#include <set>
#include <utility> 
#include <algorithm>
#include <iterator>
#include <time.h>

class Node
{
	public:
		Node(void);
		Node(int arg_target, double arg_weight);
		~Node(void);
		int target;
		double weight;
};