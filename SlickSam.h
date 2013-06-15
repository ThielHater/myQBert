#pragma once
#include "NPC.h"

enum TypeEnum {SLICK, SAM};

class SlickSam : public NPC
{
	public:
		SlickSam(Node ArgCurNode);
		~SlickSam(void);
		TypeEnum Type; // Slick oder Sam?
		int Step(const AdjacencyList &adjacency_list); // hüpft Spielfeld hinab, zufällig links/rechts
		int Collision(void); // kein Effekt
		int NodeEffect(void); // Slick setzt Feld ganz zurück, Sam setzt Feld um eine Stufe zurück
		int SetTexture(void); // Normal
};