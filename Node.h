#pragma once
#include "Cube.h"

class Node
{
	public:
		friend bool operator==(Node const &n1, Node const &n2);
		Node(void);
		Node(int ArgNodeNum, Cube* ArgCube);
		int NodeNum;
		Cube *RelCube;
};