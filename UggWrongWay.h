#pragma once
#include "NPC.h"

enum TypeEnumUW {UGG, WRONGWAY};

class UggWrongWay : public NPC
{
	public:
		UggWrongWay(Node ArgCurNode, TypeEnumUW ArgType);
		TypeEnumUW Type; // Ugg oder Wrong Way?
		textur TexLeft;
		textur TexLeftJump1;
		textur TexLeftJump2;
		textur TexLeftJump3;
		textur TexRight;
		textur TexRightJump1;
		textur TexRightJump2;
		textur TexRightJump3;
		void InitGraphics(const char *TexName);
		void Step(applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node); // bewegen sich von den unteren Ecken aus nach oben links/rechts, ungef�hr in Richtung Q*Bert
		void Collision(applikation &myqbert, GameStats &stats); // Q*Bert verliert ein Leben
		void NodeEffect(GameStats &stats); // kein Effekt
		void SetTexture(void); // drei Sprungtexturen
};