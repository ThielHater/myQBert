#pragma once
#include "NPC.h"
#include "AdjacencyList.h"

class Coily : public NPC
{
	private:
		Node Step_Unpacked(const AdjacencyList &adjacency_list, const Node qbert_cur_node);

	public:
		Coily(Node ArgCurNode);
		bool isUnpacked; // Ist Coily schon entpackt?
		textur TexUnpacked;
		textur TexUnpackedJump;
		textur TexDownLeft;
		textur TexDownLeftJump;
		textur TexDownRight;
		textur TexDownRightJump;
		textur TexUpLeft;
		textur TexUpLeftJump;
		textur TexUpRight;
		textur TexUpRightJump;
		void InitGraphics(const char *TexName);
		void Step(const applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node); // hüpft Spielfeld hinab, zufällig links/rechts, entpackt sich dann und hüpft Q*Bert hinterher
		void Collision(GameStats &stats); // Q*Bert verliert ein Leben
		void NodeEffect(GameStats &stats); // kein Effekt
		void SetTexture(void); // zwei Texturen mehr
};