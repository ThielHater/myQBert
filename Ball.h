#pragma once
#include "NPC.h"

enum TypeEnum {RED, GREEN};

class Ball : public NPC
{
	public:
		Ball(Node ArgCurNode);
		~Ball(void);
		TypeEnum Type; // Roter oder gr�ner Ball?
		textur TexNorm;
		textur TexJump;
		int Step(const AdjacencyList &adjacency_list); // h�pft Spielfeld hinab, zuf�llig links/rechts
		int Collision(void); // Rot: Q*Bert verliert ein Leben, Gr�n: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		int NodeEffect(void); // kein Effekt
		int SetTexture(void); // nur zwei Texturen
};