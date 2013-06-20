#pragma once
#include "NPC.h"

enum TypeEnumBl {RED, GREEN};

class Ball : public NPC
{
	public:
		Ball(Node ArgCurNode);
		~Ball(void);
		TypeEnumBl Type; // Roter oder gr�ner Ball?
		textur TexNorm;
		textur TexJump;
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // h�pft Spielfeld hinab, zuf�llig links/rechts
		void Collision(void); // Rot: Q*Bert verliert ein Leben, Gr�n: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		void NodeEffect(void); // kein Effekt
		void SetTexture(void); // nur zwei Texturen
};