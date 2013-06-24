#pragma once
#include "NPC.h"

enum TypeEnumBl {RED, GREEN};

class Ball : public NPC
{
	public:
		Ball(Node ArgCurNode);
		~Ball(void);
		TypeEnumBl Type; // Roter oder grüner Ball?
		textur TexNorm;
		textur TexJump;
		void InitGraphics(char *TexName);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // hüpft Spielfeld hinab, zufällig links/rechts
		void Collision(GameStats &stats); // Rot: Q*Bert verliert ein Leben, Grün: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		void NodeEffect(GameStats &stats); // kein Effekt
		void SetTexture(void); // nur zwei Texturen
};