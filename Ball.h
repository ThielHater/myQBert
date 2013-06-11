#pragma once
#include "NPC.h"

enum TypeEnum {RED, GREEN};

class Ball : public NPC
{
	public:
		Ball(void);
		~Ball(void);
		TypeEnum Type; // Roter oder grüner Ball?
		int Step(void); // hüpft Spielfeld hinab, zufällig links/rechts
		int Collision(void); // Rot: Q*Bert verliert ein Leben, Grün: Zeit wird pausiert, nur Q*Bert kann sich bewegen
		int NodeEffect(void); // kein Effekt
};