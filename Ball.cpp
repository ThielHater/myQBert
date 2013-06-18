#include "Ball.h"

Ball::Ball(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	if (Type == RED)
	{
		InitGraphics("Red-Ball");
		TexNorm.load("myQBert/Textures/Red-Ball.png");
		TexJump.load("myQBert/Textures/Red-Ball-Jump.png");
	}
	else if (Type == GREEN)
	{
		InitGraphics("Green-Ball");
		TexNorm.load("myQBert/Textures/Green-Ball.png");
		TexJump.load("myQBert/Textures/Green-Ball-Jump.png");
	}
}

Ball::~Ball(void)
{
}

int Ball::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
{
	return 0;
}

int Ball::Collision(void)
{
	return 0;
}

int Ball::NodeEffect(void)
{
	return 0;
}

int Ball::SetTexture(void)
{
	if (isMoving)
		set_texture(0, &this->TexJump);
	else
		set_texture(0, &this->TexNorm);
	return 0;
}