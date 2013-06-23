#include "NPC.h"
#include <sstream>
#include <string>

NPC::NPC(void)
{
	isMoving = false;
	isWaiting = false;
	FirstMoveDone = false;
	MoveDirection = DIR_NONE;
	FramesPerJump = 0;
	FramesPerWait = 0;
	FramesJumped = 0;
	FramesWaited = 0;
	CurNode.NodeNum = 0;
	CurNode.RelCube = 0;
	TargetNode.NodeNum = 0;
	TargetNode.RelCube = 0;
}

NPC::NPC(Node ArgCurNode)
{
	isMoving = false;
	isWaiting = false;
	FirstMoveDone = false;
	MoveDirection = DIR_NONE;
	FramesPerJump = 0;
	FramesPerWait = 0;
	FramesJumped = 0;
	FramesWaited = 0;
	CurNode=ArgCurNode;
	TargetNode.NodeNum = 0;
	TargetNode.RelCube = 0;
}

NPC::~NPC(void)
{
}

void NPC::Move(DirectionEnum direction)
{
	// Enum und Variablen
	enum FirstMoveEnum { MOVE_Y, MOVE_XZ };
	D3DXMATRIX tr;
	float sx = sqrt(50.0f) / 2 / FramesPerJump; // halbe Diagonale
	float sz = sx;
	float sy = 5.0f / FramesPerJump; // Seitenlänge

	// Textur ändern
	SetTexture();

	// Wenn wir nach unten springen, erst über die XZ Achse bewegen, sonst erst über die Y Achse
	FirstMoveEnum first_move = (MoveDirection == DIR_LEFTDOWN || MoveDirection == DIR_RIGHTDOWN) ? MOVE_XZ : MOVE_Y;

	if (first_move == MOVE_Y && !FirstMoveDone || first_move == MOVE_XZ && FirstMoveDone)
	{
		// über Y-Achse bewegen
		if (MoveDirection == DIR_LEFTDOWN || MoveDirection == DIR_RIGHTDOWN)
			D3DXMatrixTranslation(&tr, 0, -sy, 0);
		else
			D3DXMatrixTranslation(&tr, 0, sy, 0);
	}
	else
	{
		// über XZ-Achse bewegen
		if (MoveDirection == DIR_LEFTDOWN)
			D3DXMatrixTranslation(&tr, -sx, 0, -sz);
		else if (MoveDirection == DIR_LEFTUP)
			D3DXMatrixTranslation(&tr, -sx, 0, sz);
		else if (MoveDirection == DIR_RIGHTDOWN)
			D3DXMatrixTranslation(&tr, sx, 0, -sz);
		else if (MoveDirection == DIR_RIGHTUP)
			D3DXMatrixTranslation(&tr, sx, 0, sz);
	}

	// Transformation anwenden und Frames hochzählen
	add_transform(&tr);
	FramesJumped++;

	// (Teil-)Bewegung fertig?
	if (FramesJumped == FramesPerJump)
	{
		if (FirstMoveDone)
		{
			// ganze Bewegung fertig
			FramesJumped = 0;
			isMoving = false;
			isWaiting = true;
			FirstMoveDone = false;			

			// Textur ändern
			SetTexture();
		}
		else
		{
			// nur erste Teilbewegung fertig
			FramesJumped = 0;
			FirstMoveDone = true;
			CurNode = TargetNode;
		}
	}
}

void NPC::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
{
	// Wartet der NPC?
	if (isWaiting)
	{
		/* Tipp: Der Teil muss eigentlich nicht verändert werden. */

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

			/*
				Tipp: NodeEffect() und Collision() sollten am besten von hier aufgerufen werden.

				// Bewegung fertig?
				if (!isMoving)
				{
					// Würfel umfärben
					NodeEffect();

					// Sind der NPC und Q*Bert auf dem gleichen Knoten?
					if (CurNode.NodeNum == qbert_node.NodeNum)					
						Collision(stats);					
				}
			*/
		}
		else
		{
			// Ist der NPC nicht auf dem NULL Knoten?
			if (CurNode.NodeNum != 0)
			{
				/* Tipp: Mit den Indizes "1" und "2" kommt man an die Würfel unterhalb des aktuellen Würfels, mit "0" und "3" an die oberhalb. Letzteres lässt sich für Ugg und Wrong Way nutzen. */

				// neuen Knoten und damit auch die neue Richtung zufällig bestimmen
				int rnd = rand() % 2;
				if (rnd)
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
	return;
}

void NPC::InitGraphics(char *TexName)
{
	return;
}

void NPC::Collision(void)
{
	return;
}

void NPC::NodeEffect(void)
{
	return;
}

void NPC::SetTexture(void)
{
	return;
}