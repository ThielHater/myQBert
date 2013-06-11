#pragma once
#include "NPC.h"

enum TypeEnum {UGG, WRONGWAY};

class UggWrongWay : public NPC
{
	public:
		UggWrongWay(void);
		~UggWrongWay(void);
		TypeEnum Type; // Ugg oder Wrong Way?
		int Step(void); // bewegen sich von den unteren Ecken aus nach oben links/rechts, ungefähr in Richtung Q*Bert
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
};

