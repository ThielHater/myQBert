#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(void);
		QBert(Node ArgCurNode);
		~QBert(void);
		textur TexDownLeft;
		textur TexDownLeftJump;
		textur TexDownRight;
		textur TexDownRightJump;
		textur TexUpLeft;
		textur TexUpLeftJump;
		textur TexUpRight;
		textur TexUpRightJump;
		void InitGraphics(char *TexName);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, DirectionEnum direction);
		void Collision(void); // kein Effekt
		void NodeEffect(GameStats &stats); // Feld wird umgefärbt
		void SetTexture(void); // Normal
};