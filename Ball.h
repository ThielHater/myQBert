#pragma once
#include "NPC.h"

class Ball : public NPC
{
	public:
		Ball(Node ArgCurNode, char *TexName);
		textur TexNorm;
		textur TexJump;
		void InitGraphics(char *TexName);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node); // hüpft Spielfeld hinab, zufällig links/rechts
		virtual void Collision(GameStats &stats) = 0; // Rot: Q*Bert verliert ein Leben, Grün: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		void SetTexture(void); // nur zwei Texturen
};