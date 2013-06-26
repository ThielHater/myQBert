#include "Disk.h"

Disk::Disk(void)
{
	FramesPerMove=8;
	FramesMoved=0;
	isUsed=false;
}

void Disk::init_texture(textur arg_tx[])
{
	cur = 0;
	for (int i=0; i<4; i++)
		tx[i] = &arg_tx[i];	
	update_texture();
}

void Disk::update_texture(void)
{
	if (cur < 3)
		cur++;
	else
		cur=0;
	set_texture(0, tx[cur]);
}