#include <sstream>
#include <string>
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

void QBert::InitGraphics(char *TexName)
{
	D3DXMATRIX pos;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	CurNode.RelCube->get_transform(&pos);
	D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
	D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
	load("TriPrism.x", "myQBert/Models");
	std::stringstream ss;
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Left.png";
	TexDownLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Left-Jump.png";
	TexDownLeftJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Right.png";
	TexDownRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Right-Jump.png";
	TexDownRightJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Left.png";
	TexUpLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Left-Jump.png";
	TexUpLeftJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Right.png";
	TexUpRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Right-Jump.png";
	TexUpRightJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	set_texture(0, &TexDownLeft);
	disable_reflections();
	add_transform(&rota);
	add_transform(&pos);
	add_transform(&trans);
	return;
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
				if (CurNode.NodeNum != 0)
					NodeEffect(stats);
			}
		}
		else
		{
			// Soll der NPC sich bewegen?
			if (direction != DIR_NONE)
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

void QBert::Collision(GameStats &stats)
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