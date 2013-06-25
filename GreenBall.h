#pragma once
#include "ball.h"
class GreenBall :
	public Ball
{
public:
	GreenBall(Node ArgCurNode);
	void Collision(GameStats &stats);
};

