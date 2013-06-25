#pragma once
#include "SpaCE\objekt.h"

class Cube : public objekt
{
	public:
		textur *tx[3];		
		int cur;
		void init_texture(textur arg_tx[]);
		void update_texture(void);
};