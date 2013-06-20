#pragma once
#include "NPC.h"
#include "AdjacencyList.h"

class Coily : public NPC
{
	private:
		Node Step_Unpacked(const AdjacencyList &adjacency_list, const Node qbert_node);

	public:
		Coily(Node ArgCurNode);
		~Coily(void);
		bool isUnpacked; // Ist Coily schon entpackt?
		textur TexUnpacked;
		textur TexUnpackedJump;
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // hüpft Spielfeld hinab, zufällig links/rechts, entpackt sich dann und hüpft Q*Bert hinterher
		void Collision(GameStats &stats); // Q*Bert verliert ein Leben
		void NodeEffect(void); // kein Effekt
		void SetTexture(void); // zwei Texturen mehr
};