#include "Cube.h"

Cube::Cube(void)
{
}

Cube::~Cube(void)
{
}

void Cube::init_texture(textur arg_tx[])
{
	cur = 0;
	for (int i=0; i<3; i++)
		tx[i] = &arg_tx[i];	
	update_texture();
}

void Cube::update_texture(void)
{
	set_texture(0, tx[cur]);
}