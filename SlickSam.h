#pragma once
#include "NPC.h"

enum TypeEnum {SLICK, SAM};

class SlickSam : public NPC
{
	public:
		SlickSam(Node ArgCurNode);
		~SlickSam(void);
		TypeEnum Type; // Slick oder Sam?
		int Step(void); // h�pft Spielfeld hinab, zuf�llig links/rechts
		int Collision(void); // kein Effekt
		int NodeEffect(void); // Slick setzt Feld ganz zur�ck, Sam setzt Feld um eine Stufe zur�ck
};