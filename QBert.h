#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(void);
		QBert(Node ArgCurNode);
		~QBert(void);
		int Collision(void); // kein Effekt
		int NodeEffect(void); // Feld wird umgefärbt
};
