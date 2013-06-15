#pragma once
#include "Cube.h"

class Disk : public Cube
{
	public:
		Disk(void);
		~Disk(void);
		bool isUsed;
		textur *FirstTex;
		textur *CurTex;
		textur *LastTex;
		int Move(void); // wird aufgerufen, wenn Q*Bert auf die Disk hüpft
};