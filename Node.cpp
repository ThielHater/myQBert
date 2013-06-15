#include "Node.h"

Node::Node(void)
{
	NodeNum = 0;
	RelCube = 0;
}

Node::Node(int ArgNodeNum, Cube* ArgCube)
{
	NodeNum = ArgNodeNum;
	RelCube = ArgCube;
}

Node::~Node(void)
{
}