#include "Ball.h"

Ball::Ball(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	int rnd = rand() % 2;
	if (rnd%2)
	{
		Type = RED;
		InitGraphics("Red-Ball");
		TexNorm.load("myQBert/Textures/Red-Ball.png");
		TexJump.load("myQBert/Textures/Red-Ball-Jump.png");
	}
	else
	{
		Type = GREEN;
		InitGraphics("Green-Ball");
		TexNorm.load("myQBert/Textures/Green-Ball.png");
		TexJump.load("myQBert/Textures/Green-Ball-Jump.png");
	}
}

Ball::~Ball(void)
{
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