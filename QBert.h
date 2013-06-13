#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(void);
		~QBert(void);
		int Step(void); // bewegt sich gem‰ﬂ Eingabe auf dem Spielfeld
		int Collision(void); // kein Effekt
		int NodeEffect(void); // Feld wird umgef‰rbt
};