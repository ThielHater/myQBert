#pragma once
#include "Cube.h"

class Disk : public Cube
{
	public:
		Disk(void);
		textur *tx[4];
		int FramesPerMove;
		int FramesMoved;
		int cur;
		bool isUsed;
		void init_texture(textur arg_tx[]);
		void update_texture(void);
};