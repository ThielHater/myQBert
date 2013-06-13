#pragma once
#include "NPC.h"
#include "Node.h"
#include "AdjacencyList.h"

class Coily : public NPC
{
	private:
		int Step_Unpacked(const AdjacencyList &adjacency_list, int qbert_node);

	public:
		Coily(int coily_node);
		~Coily(void);
		bool isUnpacked; // Ist Coily schon entrollt?
		int Step(const AdjacencyList &adjacency_list, int qbert_node); // h�pft Spielfeld hinab, zuf�llig links/rechts, entrollt sich dann und h�pft Q*Bert hinterher		
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
};