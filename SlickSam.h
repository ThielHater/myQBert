#pragma once
#include "NPC.h"

enum TypeEnumSS {SLICK, SAM};

class SlickSam : public NPC
{
	public:
		SlickSam(Node ArgCurNode);
		TypeEnumSS Type; // Slick oder Sam?
		textur TexLeft;
		textur TexLeftJump1;
		textur TexLeftJump2;
		textur TexLeftJump3;
		textur TexRight;
		textur TexRightJump1;
		textur TexRightJump2;
		textur TexRightJump3;
		void InitGraphics(const char *TexName);
		void Step(const applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node); // hüpft Spielfeld hinab, zufällig links/rechts
		void Collision(GameStats &stats); // kein Effekt
		void NodeEffect(GameStats &stats); // Slick setzt Feld ganz zurück, Sam setzt Feld um eine Stufe zurück
		void SetTexture(void); // drei Sprungtexturen
};