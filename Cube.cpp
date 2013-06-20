#include "Cube.h"

Cube::Cube(void)
{
}

Cube::~Cube(void)
{
}

bool Cube::IsDone() {
	return CurTex == LastTex;
}