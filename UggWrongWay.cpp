#include <sstream>
#include <string>
#include "UggWrongWay.h"

UggWrongWay::UggWrongWay(Node ArgCurNode, TypeEnumUW ArgType) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	Type = ArgType;
	if (Type == UGG)
		InitGraphics("Ugg");
	else
		InitGraphics("Wrong-Way");
}

void UggWrongWay::InitGraphics(const char *TexName)
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

void UggWrongWay::Step(applikation &myqbert, const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node)
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
			}
		}
		else
		{
			// Sind der NPC und Q*Bert nicht auf dem gleichen Knoten?
			if (CurNode.NodeNum != qbert_cur_node.NodeNum)
			{
				// neuen Knoten und damit auch die neue Richtung zuf�llig bestimmen
				int rnd = rand() % 2;
				if (Type == UGG)
				{
					// W�rde Ugg nicht abst�rzen, wenn er nach unten geht?
					if (rnd && (adjacency_list[CurNode.NodeNum][1].target.NodeNum != 0))
					{
						TargetNode = adjacency_list[CurNode.NodeNum][1].target;
						MoveDirection = DIR_RIGHTDOWN;
					}
					else
					{
						TargetNode = adjacency_list[CurNode.NodeNum][0].target;
						MoveDirection = DIR_RIGHTUP;
					}
				}
				else
				{
					// W�rde Wrong Way nicht abst�rzen, wenn er nach unten geht?
					if (rnd && (adjacency_list[CurNode.NodeNum][2].target.NodeNum != 0))
					{
						TargetNode = adjacency_list[CurNode.NodeNum][2].target;
						MoveDirection = DIR_LEFTDOWN;
					}
					else
					{
						TargetNode = adjacency_list[CurNode.NodeNum][3].target;
						MoveDirection = DIR_LEFTUP;
					}
				}

				// Ist Ugg/Wrong Way nicht auf eine Scheibe geh�pft?
				if ((TargetNode.NodeNum != 29) && (TargetNode.NodeNum != 30))
				{
					// Sound abspielen
					myqbert.play_sound(12, 0);

					// NPC bewegen
					isMoving = true;
					Move(MoveDirection);
				}
				else
				{
					// Ugg/Wrong Way f�llt
					CurNode.NodeNum = 0;
				}
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

void UggWrongWay::Collision(applikation &myqbert, GameStats &stats)
{
	stats.LifeCount--;
	stats.QBertHit = (stats.LifeCount != 0);
	if (Type == UGG)
	{
		if (stats.LifeCount > 0)
			printf("Q*Bert wurde von Ugg gefangen, noch %d Leben!\n", stats.LifeCount);
		else
			printf("Q*Bert wurde von Ugg gefangen, kein Leben mehr!\n", stats.LifeCount);
	}
	else
	{
		if (stats.LifeCount > 0)
			printf("Q*Bert wurde von Wrong Way gefangen, noch %d Leben!\n", stats.LifeCount);
		else
			printf("Q*Bert wurde von Wrong Way gefangen, kein Leben mehr!\n", stats.LifeCount);
	}
	myqbert.play_sound(11, 0);
	return;
}

void UggWrongWay::NodeEffect(GameStats &stats)
{
	return;
}

void UggWrongWay::SetTexture(void)
{
	if (isMoving)
	{		
		int rnd = rand() % 3;
		if ((MoveDirection == DIR_LEFTUP) || (MoveDirection == DIR_RIGHTDOWN))
		{
			if (rnd == 0)
				set_texture(0, &this->TexLeftJump1);
			else if (rnd == 1)
				set_texture(0, &this->TexLeftJump2);
			else
				set_texture(0, &this->TexLeftJump3);
		}
		else if ((MoveDirection == DIR_RIGHTUP) || (MoveDirection == DIR_LEFTDOWN))
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
		if ((MoveDirection == DIR_LEFTUP) || (MoveDirection == DIR_RIGHTDOWN))
			set_texture(0, &this->TexLeft);
		else if ((MoveDirection == DIR_RIGHTUP) || (MoveDirection == DIR_LEFTDOWN))
			set_texture(0, &this->TexRight);
	}
	return;
}