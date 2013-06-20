#include "UggWrongWay.h"

UggWrongWay::UggWrongWay(Node ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	int rnd = rand() % 2;
	if (rnd%2)
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

void UggWrongWay::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node)
{
	return;
}

void UggWrongWay::Collision(void)
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