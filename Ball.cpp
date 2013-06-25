#include <sstream>
#include <string>
#include "Ball.h"

Ball::Ball(Node ArgCurNode, const char *TexName) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	InitGraphics(TexName);
}

void Ball::InitGraphics(const char *TexName)
{
	D3DXMATRIX pos;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	CurNode.RelCube->get_transform(&pos);
	D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
	D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
	load("TriPrism.x", "myQBert/Models");
	std::stringstream ss;
	ss <<"myQBert/Textures/" <<TexName <<".png";
	TexNorm.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Jump.png";
	TexJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	set_texture(0, &TexNorm);
	disable_reflections();
	add_transform(&rota);
	add_transform(&pos);
	add_transform(&trans);
	return;
}

void Ball::Step(const applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node)
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

			// Springen der NPC und Q*Bert sich entgegen?
			if ((CurNode.NodeNum == qbert_tar_node.NodeNum) && (TargetNode.NodeNum == qbert_cur_node.NodeNum))
				Collision(stats);

			// Bewegung fertig?
			if (!isMoving)
			{
				// Sind der NPC und Q*Bert auf dem gleichen Knoten?
				if (CurNode.NodeNum == qbert_cur_node.NodeNum)					
					Collision(stats);					
			}
		}
		else
		{
			// Sind der NPC und Q*Bert nicht auf dem gleichen Knoten?
			if (CurNode.NodeNum != qbert_cur_node.NodeNum)
			{
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
			else
			{
				// Kollision
				Collision(stats);
			}
		}
	}
	return;
}

void Ball::SetTexture(void)
{
	if (isMoving)
		set_texture(0, &this->TexJump);
	else
		set_texture(0, &this->TexNorm);
	return;
}