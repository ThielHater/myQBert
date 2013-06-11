#pragma once
#include "NPC.h"

class Coily : public NPC
{
	public:
		Coily(void);
		~Coily(void);
		bool isUnpacked; // Ist Coily schon entrollt?
		int Step(void); // hüpft Spielfeld hinab, zufällig links/rechts, entrollt sich dann und hüpft Q*Bert hinterher
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
};