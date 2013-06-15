#pragma once
#include "NPC.h"
#include "AdjacencyList.h"

class Coily : public NPC
{
	private:
		Node Step_Unpacked(const AdjacencyList &adjacency_list, Node qbert_node);

	public:
		Coily(Node ArgCurNode);
		~Coily(void);
		bool isUnpacked; // Ist Coily schon entrollt?
		int Step(const AdjacencyList &adjacency_list, Node qbert_node); // hüpft Spielfeld hinab, zufällig links/rechts, entrollt sich dann und hüpft Q*Bert hinterher		
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
};