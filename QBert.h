#pragma once
#include "NPC.h"

class QBert : public NPC
{
	public:
		QBert(Node ArgCurNode);
		textur TexDownLeft;
		textur TexDownLeftJump;
		textur TexDownLeftBalloon;
		textur TexDownRight;
		textur TexDownRightJump;
		textur TexDownRightBalloon;
		textur TexUpLeft;
		textur TexUpLeftJump;
		textur TexUpLeftBalloon;
		textur TexUpRight;
		textur TexUpRightJump;
		textur TexUpRightBalloon;
		void InitGraphics(char *TexName);
		void Step(const AdjacencyList &adjacency_list, GameStats &stats, DirectionEnum direction);
		void Collision(GameStats &stats); // kein Effekt
		void NodeEffect(GameStats &stats); // Feld wird umgefärbt
		void SetTexture(void); // Normal
};