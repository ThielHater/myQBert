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

void SlickSam::InitGraphics(const char *TexName)
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

void SlickSam::Step(applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node)
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
				Collision(myqbert, stats);

			// Bewegung fertig?
			if (!isMoving)
			{
				// Sind der NPC und Q*Bert auf dem gleichen Knoten?
				if (CurNode.NodeNum == qbert_cur_node.NodeNum)					
					Collision(myqbert, stats);					

				// Würfel umfärben
				if (CurNode.NodeNum != 0)
					NodeEffect(stats);
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

				// Sound abspielen
				myqbert.play_sound(12, 0);

				// NPC bewegen
				isMoving = true;
				Move(MoveDirection);
			}
			else
			{
				// Kollision
				Collision(myqbert, stats);
			}
		}
	}
	return;
}

void SlickSam::Collision(applikation &myqbert, GameStats &stats)
{	
	stats.Score += 300;
	CurNode.NodeNum = 0;
	if (Type == SLICK)
		printf("Q*Bert hat Slick gefangen!");
	else
		printf("Q*Bert hat Sam gefangen!");
	myqbert.play_sound(21, 0);
	return;
}

void SlickSam::NodeEffect(GameStats &stats)
{
	// Ist der Würfel zurückfärbbar?
	if (CurNode.RelCube->cur > 0)
	{
		// Punkte aktualisieren
		if (CurNode.RelCube->cur == 2)
		{
			if (Type == SLICK)
				stats.Score -= 40;
			else
				stats.Score -= 25;
		}
		else if (CurNode.RelCube->cur == 1)
		{
			if (stats.Level == 2)
				stats.Score -= 15;
			else
				stats.Score -= 25;
		}

		// Würfel umfärben (1. Farbe oder vorherige Farbe)
		if (Type == SLICK)
			this->CurNode.RelCube->cur = 0;
		else
			this->CurNode.RelCube->cur--;
		this->CurNode.RelCube->update_texture();
	}
	return;
}

void SlickSam::SetTexture(void)
{
	if (isMoving)
	{
		int rnd = rand() % 3;
		if (MoveDirection == DIR_LEFTDOWN)
		{
			if (rnd == 0)
				set_texture(0, &this->TexLeftJump1);
			else if (rnd == 1)
				set_texture(0, &this->TexLeftJump2);
			else
				set_texture(0, &this->TexLeftJump3);
		}
		else if (MoveDirection == DIR_RIGHTDOWN)
		{
			if (rnd == 0)
				set_texture(0, &this->TexRightJump1);
			else if (rnd == 1)
				set_texture(0, &this->TexRightJump2);
			else
				set_texture(0, &this->TexRightJump3);
		}
	}
	else
	{
		if (MoveDirection == DIR_LEFTDOWN)
			set_texture(0, &this->TexLeft);
		else if (MoveDirection == DIR_RIGHTDOWN)
			set_texture(0, &this->TexRight);
	}
	return;
}