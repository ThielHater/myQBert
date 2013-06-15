#pragma once
#include "Cube.h"

class Node
{
	public:
		Node(void);
		Node(int ArgNodeNum, Cube* ArgCube);
		~Node(void);
		int NodeNum;
		Cube *RelCube;
};
