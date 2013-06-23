#include <sstream>
#include <string>
#include "UggWrongWay.h"

UggWrongWay::UggWrongWay(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	int rnd = rand() % 2;
	if (rnd)
	{
		Type = UGG;
		InitGraphics("Ugg");
	}
	else
	{
		Type = WRONGWAY;
		InitGraphics("Wrong-Way");
	}
}

UggWrongWay::~UggWrongWay(void)
{
}

void UggWrongWay::InitGraphics(char *TexName)
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

void UggWrongWay::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
{
	/*
	if (Type == UGG)
	{
		TargetNode = adjacency_list[CurNode.NodeNum][0].target;
		MoveDirection = DIR_RIGHTUP;
	}
	else if (Type == WRONGWAY)
	{
		TargetNode = adjacency_list[CurNode.NodeNum][3].target;
		MoveDirection = DIR_LEFTUP;
	}
	*/
	return;
}

void UggWrongWay::Collision(GameStats &stats)
{
	return;
}

void UggWrongWay::NodeEffect(void)
{
	return;
}

void UggWrongWay::SetTexture(void)
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
	return;
}