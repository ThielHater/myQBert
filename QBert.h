#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(void);
		QBert(Node ArgCurNode);
		~QBert(void);
		int Step(const AdjacencyList &adjacency_list, GameStats &stats, DirectionEnum direction);
		int Collision(void); // kein Effekt
		int NodeEffect(GameStats &stats); // Feld wird umgefärbt
		int SetTexture(void); // Normal
		void Reset(Node &node);
};