#include "SlickSam.h"

SlickSam::SlickSam(Node ArgCurNode, TypeEnum t) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	Type = t;
	if (Type == SLICK)
		InitGraphics("Slick");
	else if (Type == SAM)
		InitGraphics("Sam");
}

SlickSam::~SlickSam(void)
{
}

int SlickSam::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
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
		// Bewegung fertig?
		if(!isMoving)
		{
			NodeEffect();
		}
	}
	else
	{
		// Bewegt sich der NPC?
		if (isMoving)
		{
			// Weiter bewegen..
			Move(MoveDirection);

			// Sind Coily und Q*Bert auf dem gleichen Knoten?
			if (CurNode.NodeNum == qbert_node.NodeNum)
			{
				// Q*Bert hat Slick/Sam gefangen
				Collision();
			}
		}
		else
		{
			// Ist der NPC nicht auf dem NULL Knoten?
			if (CurNode.NodeNum != 0)
			{
				// neuen Knoten und damit auch die neue Richtung zufällig bestimmen
				int rnd = rand() % 2;
				if (rnd%2)
				{
					TargetNode = adjacency_list[CurNode.NodeNum][1].target;
					MoveDirection = DIR_RIGHTDOWN;
				}
				else
				{
					TargetNode = adjacency_list[CurNode.NodeNum][2].target;
					MoveDirection = DIR_LEFTDOWN;
				}

				// NPC bewegen
				isMoving = true;
				Move(MoveDirection);
			}
		}
	}
	return 0;
}

int SlickSam::Collision()
{
	printf("Great you catched Slick/Sam");
	return 0;
}

int SlickSam::NodeEffect(void)
{
	if(Type == SLICK)
	{
		// Würfel umfärben (1. Farbe)
		this->CurNode.RelCube->set_texture(0, this->CurNode.RelCube->FirstTex);
	}
	else
	{
		// Würfel umfärben (Farbe - 1)
		if(CurNode.RelCube->CurTex != CurNode.RelCube->FirstTex)
		{
			this->CurNode.RelCube->set_texture(0, this->CurNode.RelCube->CurTex-1);
		}
	}
	return 0;
}

int SlickSam::SetTexture(void)
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
	return 0;
}