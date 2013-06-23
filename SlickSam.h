#pragma once
#include "NPC.h"

enum TypeEnumSS {SLICK, SAM};

class SlickSam : public NPC
{
	public:
		SlickSam(Node ArgCurNode);
		~SlickSam(void);
		TypeEnumSS Type; // Slick oder Sam?
		textur TexLeft;
		textur TexLeftJump1;
		textur TexLeftJump2;
		textur TexLeftJump3;
		textur TexRight;
		textur TexRightJump1;
		textur TexRightJump2;
		textur TexRightJump3;
		void InitGraphics(char *TexName);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // hüpft Spielfeld hinab, zufällig links/rechts
		void Collision(void); // kein Effekt
		void NodeEffect(void); // Slick setzt Feld ganz zurück, Sam setzt Feld um eine Stufe zurück
		void SetTexture(void); // drei Sprungtexturen
};