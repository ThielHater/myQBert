#include "Node.h"

bool operator==(Node const &n1, Node const &n2)
{
	return (n1.NodeNum == n2.NodeNum);
}

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