#pragma once
#include "NPC.h"

class QBert : public NPC
{

	public:
		enum qbert_direction {
			LEFTDOWN,
			LEFTUP,
			RIGHTDOWN,
			RIGHTUP
		};

	private:
		D3DXVECTOR3 move_vector;
		bool is_moving;
		qbert_direction move_direction;

	public:
		QBert(void);
		~QBert(void);
		void move(qbert_direction direction);
		int Step(); // bewegt sich gem‰ﬂ Eingabe auf dem Spielfeld
		int Collision(void); // kein Effekt
		int NodeEffect(void); // Feld wird umgef‰rbt
};

