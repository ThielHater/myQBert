#pragma once
#include "ball.h"
class RedBall :
	public Ball
{
public:
	RedBall(Node ArgCurNode);
	void Collision(GameStats &stats);
};

