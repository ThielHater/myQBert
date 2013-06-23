#pragma once
#include "Cube.h"

class Disk : public Cube
{
	public:
		Disk(void);
		~Disk(void);
		textur *tx[4];
		int cur;
		bool isUsed;
		int Move(void); // wird aufgerufen, wenn Q*Bert auf die Disk hüpft
};