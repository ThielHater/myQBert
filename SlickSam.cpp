#include <sstream>
#include <string>
#include "SlickSam.h"

SlickSam::SlickSam(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	int rnd = rand() % 2;
	if (rnd)
	{
		Type = SLICK;
		InitGraphics("Slick");
	}
	else
	{
		Type = SAM;
		InitGraphics("Sam");
	}
}

SlickSam::~SlickSam(void)
{
}

void SlickSam::InitGraphics(char *TexName)
{
	D3DXMATRIX pos;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	CurNode.RelCube->get_transform(&pos);
	D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
	D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
	load("TriPrism.x", "myQBert/Models");
	std::stringstream ss;
	ss <<"myQBert/Textures/" <<TexName <<"-Left.png";
	TexLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Left-Jump-1.png";
	TexLeftJump1.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Left-Jump-2.png";
	TexLeftJump2.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Left-Jump-3.png";
	TexLeftJump3.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Right.png";
	TexRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Right-Jump-1.png";
	TexRightJump1.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Right-Jump-2.png";
	TexRightJump2.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Right-Jump-3.png";
	TexRightJump3.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	set_texture(0, &TexLeft);
	disable_reflections();
	add_transform(&rota);
	add_transform(&pos);
	add_transform(&trans);
	return;
}

void SlickSam::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
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

void SlickSam::Collision(void)
{
	if (Type == SLICK)
		printf("Q*Bert hat Slick gefangen!");
	else
		printf("Q*Bert hat Sam gefangen!");
	return;
}

void SlickSam::NodeEffect(void)
{
	if (Type == SLICK)
	{
		// Würfel umfärben (erste Farbe)
		this->CurNode.RelCube->cur = 0;
		this->CurNode.RelCube->update_texture();
	}
	else if (Type == SAM)
	{
		// Würfel umfärben (vorherige Farbe)		
		if (CurNode.RelCube->cur > 0)
		{
			this->CurNode.RelCube->cur--;
			this->CurNode.RelCube->update_texture();	
		}
	}
	return;
}

void SlickSam::SetTexture(void)
{
	if (isMoving)
	{
		int rnd = 1 + rand() % 3;
		if (MoveDirection == DIR_LEFTUP)
		{
			if (rnd == 1)				
				set_texture(0, &this->TexLeftJump1);
			else if (rnd == 2)
				set_texture(0, &this->TexLeftJump2);
			else
				set_texture(0, &this->TexLeftJump3);
		}
		else if (MoveDirection == DIR_RIGHTUP)
		{		
			if (rnd == 1)				
				set_texture(0, &this->TexRightJump1);
			else if (rnd == 2)
				set_texture(0, &this->TexRightJump2);
			else
				set_texture(0, &this->TexRightJump3);
		}
	}
	else
	{
		if (MoveDirection == DIR_LEFTUP)
			set_texture(0, &this->TexLeft);
		else if (MoveDirection == DIR_RIGHTUP)
			set_texture(0, &this->TexRight);
	}
	return;}