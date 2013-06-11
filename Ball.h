#pragma once
#include "NPC.h"

enum TypeEnum {RED, GREEN};

class Ball : public NPC
{
	public:
		Ball(void);
		~Ball(void);
		TypeEnum Type; // Roter oder gr�ner Ball?
		int Step(void); // h�pft Spielfeld hinab, zuf�llig links/rechts
		int Collision(void); // Rot: Q*Bert verliert ein Leben, Gr�n: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		int NodeEffect(void); // kein Effekt
};