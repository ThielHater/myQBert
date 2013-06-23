#include <sstream>
#include <string>
#include "Ball.h"

Ball::Ball(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	int rnd = rand() % 2;
	if (rnd)	
	{
		Type = RED;
		InitGraphics("Red-Ball");
	}
	else
	{
		Type = GREEN;
		InitGraphics("Green-Ball");
	}
}

Ball::~Ball(void)
{
}

void Ball::InitGraphics(char *TexName)
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

void Ball::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
{
	return;
}

void Ball::Collision(void)
{
	return;
}

void Ball::NodeEffect(void)
{
	return;
}

void Ball::SetTexture(void)
{
	if (isMoving)
		set_texture(0, &this->TexJump);
	else
		set_texture(0, &this->TexNorm);
}