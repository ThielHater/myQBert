#include "SlickSam.h"

SlickSam::SlickSam(Node ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	if (Type == SLICK)
		InitGraphics("Slick");
	else if (Type == SAM)
		InitGraphics("Sam");
}

SlickSam::~SlickSam(void)
{
}

int SlickSam::Step(const AdjacencyList &adjacency_list)
{
	return 0;
}

int SlickSam::Collision(void)
{
	return 0;
}

int SlickSam::NodeEffect(void)
{
	return 0;
}

int SlickSam::SetTexture(void)
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
	return 0;
}