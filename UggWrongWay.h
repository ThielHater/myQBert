#pragma once
#include "NPC.h"

enum TypeEnumUW {UGG, WRONGWAY};

class UggWrongWay : public NPC
{
	public:
		UggWrongWay(Node ArgCurNode);
		~UggWrongWay(void);
		TypeEnumUW Type; // Ugg oder Wrong Way?
		textur TexLeft;
		textur TexLeftJump1;
		textur TexLeftJump2;
		textur TexLeftJump3;
		textur TexRight;
		textur TexRightJump1;
		textur TexRightJump2;
		textur TexRightJump3;
		void InitGraphics(char *TexName);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // bewegen sich von den unteren Ecken aus nach oben links/rechts, ungefähr in Richtung Q*Bert
		void Collision(void); // Q*Bert verliert ein Leben
		void NodeEffect(void); // kein Effekt
		void SetTexture(void); // drei Sprungtexturen
};