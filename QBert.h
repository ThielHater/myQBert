#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(void);
		QBert(Node ArgCurNode);
		~QBert(void);
		int Step(const AdjacencyList &adjacency_list, DirectionEnum direction);
		int Collision(void); // kein Effekt
		int NodeEffect(void); // Feld wird umgefärbt
		int SetTexture(void); // Normal
};