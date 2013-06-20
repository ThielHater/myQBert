#pragma once
#include "NPC.h"

enum TypeEnumUW {UGG, WRONGWAY};

class UggWrongWay : public NPC
{
	public:
		UggWrongWay(Node ArgCurNode);
		~UggWrongWay(void);
		TypeEnumUW Type; // Ugg oder Wrong Way?
		int Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // bewegen sich von den unteren Ecken aus nach oben links/rechts, ungef�hr in Richtung Q*Bert
		int Collision(void); // Q*Bert verliert ein Leben
		int NodeEffect(void); // kein Effekt
		int SetTexture(void); // drei Sprungtexturen
};