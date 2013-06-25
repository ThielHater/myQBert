#pragma once
#include "Ball.h"

class GreenBall : public Ball
{
	public:
		GreenBall(Node ArgCurNode);
		void Collision(applikation &myqbert, GameStats &stats);
};