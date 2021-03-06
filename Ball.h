#pragma once
#include "NPC.h"

class Ball : public NPC
{
	public:
		Ball(Node ArgCurNode, const char *TexName);
		textur TexNorm;
		textur TexJump;
		void InitGraphics(const char *TexName);
		void Step(applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node); // h�pft Spielfeld hinab, zuf�llig links/rechts
		virtual void Collision(applikation &myqbert, GameStats &stats) = 0; // Rot: Q*Bert verliert ein Leben, Gr�n: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		void SetTexture(void); // nur zwei Texturen
};