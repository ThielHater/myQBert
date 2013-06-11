#pragma once
#include "NPC.h"

class Coily : public NPC
{
	public:
		Coily(void);
		~Coily(void);
		bool isUnpacked; // Ist Coily schon entrollt?
		int Step(void); // h�pft Spielfeld hinab, zuf�llig links/rechts, entrollt sich dann und h�pft Q*Bert hinterher
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
};