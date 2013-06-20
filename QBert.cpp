#include "Qbert.h"

QBert::QBert(void)
{
}

QBert::QBert(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 4;
	FramesPerWait = 4;
	InitGraphics("QBert");
}

QBert::~QBert(void)
{
}

void QBert::Step(const AdjacencyList &adjacency_list, GameStats &stats, DirectionEnum direction)
{
	// Wartet der NPC?
	if (isWaiting)
	{
		// Weiter warten..
		FramesWaited++;

		// Hat der NPC genug gewartet?
		if (FramesWaited == FramesPerWait)
		{
			// Freigeben
			FramesWaited = 0;
			isWaiting = false;
		}
	}
	else
	{
		// Bewegt sich der NPC?
		if (isMoving)
		{
			// Weiter bewegen..
			Move(MoveDirection);

			// Bewegung fertig?
			if (!isMoving)
			{
				// Würfel umfärben
				NodeEffect(stats);
			}
		}
		else
		{
			// Ist der NPC nicht auf dem NULL Knoten?
			if ((CurNode.NodeNum != 0) && (direction != DIR_NONE))
			{
				// nächsten Knoten und Richtung gemäß Tastatureingabe festlegen
				if (direction == DIR_RIGHTUP)
					TargetNode = adjacency_list[CurNode.NodeNum][0].target;
				else if (direction == DIR_RIGHTDOWN)
					TargetNode = adjacency_list[CurNode.NodeNum][1].target;
				else if (direction == DIR_LEFTDOWN)
					TargetNode = adjacency_list[CurNode.NodeNum][2].target;
				else if (direction == DIR_LEFTUP)
					TargetNode = adjacency_list[CurNode.NodeNum][3].target;
				MoveDirection = direction;

				// NPC bewegen
				isMoving = true;
				Move(MoveDirection);
			}
		}
	}

	return;
}

void QBert::Collision(void)
{
	return;
}

void QBert::NodeEffect(GameStats &stats)
{
	if ((stats.Level == 1) || (stats.Level == 2))
	{
		if (this->CurNode.RelCube->cur < stats.Level)
		{
			this->CurNode.RelCube->cur++;
			this->CurNode.RelCube->update_texture();
			stats.Score += 25;
		}
	}
	else if (stats.Level == 3)
	{
		if (this->CurNode.RelCube->cur == 0)
		{
			this->CurNode.RelCube->cur++;
			stats.Score += 25;
		}
		else
		{
			this->CurNode.RelCube->cur--;
			stats.Score -= 25;
		}
		this->CurNode.RelCube->update_texture();
	}
	return;
}

void QBert::SetTexture(void)
{
	if (isMoving)
	{
		if (MoveDirection == DIR_LEFTDOWN)
			set_texture(0, &this->TexDownLeftJump);
		else if (MoveDirection == DIR_RIGHTDOWN)
			set_texture(0, &this->TexDownRightJump);
		else if (MoveDirection == DIR_LEFTUP)
			set_texture(0, &this->TexUpLeftJump);
		else if (MoveDirection == DIR_RIGHTUP)
			set_texture(0, &this->TexUpRightJump);
	}
	else
	{
		if (MoveDirection == DIR_LEFTDOWN)
			set_texture(0, &this->TexDownLeft);
		else if (MoveDirection == DIR_RIGHTDOWN)
			set_texture(0, &this->TexDownRight);
		else if (MoveDirection == DIR_LEFTUP)
			set_texture(0, &this->TexUpLeft);
		else if (MoveDirection == DIR_RIGHTUP)
			set_texture(0, &this->TexUpRight);
	}
	return;
}