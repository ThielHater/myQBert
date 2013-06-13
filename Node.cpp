#include "Node.h"

Node::Node(void)
{
	target=0;
	weight=0;
}

Node::Node(int arg_target, double arg_weight)
{
	target=arg_target;
	weight=arg_weight;
}

Node::~Node(void)
{
}