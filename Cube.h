#pragma once
#include "SpaCE\objekt.h"

class Cube : public objekt
{
	public:
		Cube(void);
		~Cube(void);
		textur *FirstTex;
		textur *CurTex;
		textur *LastTex;
};

