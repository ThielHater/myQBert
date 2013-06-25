#pragma once
#include "Ball.h"

class RedBall : public Ball
{
	public:
		RedBall(Node ArgCurNode);
		void Collision(applikation &myqbert, GameStats &stats);
};