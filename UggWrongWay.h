#pragma once
#include "NPC.h"

enum TypeEnum {UGG, WRONGWAY};

class UggWrongWay : public NPC
{
	public:
		UggWrongWay(Node ArgCurNode);
		~UggWrongWay(void);
		TypeEnum Type; // Ugg oder Wrong Way?
		int Step(const AdjacencyList &adjacency_list); // bewegen sich von den unteren Ecken aus nach oben links/rechts, ungefähr in Richtung Q*Bert
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
		int SetTexture(void); // drei Sprungtexturen
};