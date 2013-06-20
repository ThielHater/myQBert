#pragma once
#include "NPC.h"

enum TypeEnumUW {UGG, WRONGWAY};

class UggWrongWay : public NPC
{
	public:
		UggWrongWay(Node ArgCurNode);
		~UggWrongWay(void);
		TypeEnumUW Type; // Ugg oder Wrong Way?
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // bewegen sich von den unteren Ecken aus nach oben links/rechts, ungefähr in Richtung Q*Bert
		void Collision(void); // Q*Bert verliert ein Leben
		void NodeEffect(void); // kein Effekt
		void SetTexture(void); // drei Sprungtexturen
};