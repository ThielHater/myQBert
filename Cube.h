#pragma once
#include "SpaCE\objekt.h"
#include "GameStats.h"

class Cube : public objekt
{
	public:
		Cube(void);
		~Cube(void);
		textur *tx[3];		
		int cur;
		void init_texture(textur arg_tx[]);
		void update_texture(void);
};