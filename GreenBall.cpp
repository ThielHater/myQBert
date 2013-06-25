#include "GreenBall.h"
#include "Ball.h"
#include "Node.h"

GreenBall::GreenBall(Node ArgCurNode) : Ball(ArgCurNode, "Green-Ball")
{
}

void GreenBall::Collision(GameStats &stats)
{
	stats.TimeFrozen = true;
	stats.Score += 100;
	printf("Q*Bert hat den gr\fcnen Ball gefangen, die Zeit steht still!\n");
}