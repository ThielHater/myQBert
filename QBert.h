#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(void);
		QBert(Node ArgCurNode);
		~QBert(void);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, DirectionEnum direction);
		void Collision(void); // kein Effekt
		void NodeEffect(GameStats &stats); // Feld wird umgefärbt
		void SetTexture(void); // Normal
		void Reset();
};