#include "GreenBall.h"
#include "Ball.h"
#include "Node.h"

GreenBall::GreenBall(Node ArgCurNode) : Ball(ArgCurNode, "Green-Ball")
{
}

void GreenBall::Collision(applikation &myqbert, GameStats &stats)
{
	stats.TimeFrozen = true;
	stats.Score += 100;
	printf("Q*Bert hat den gr\fcnen Ball gefangen, die Zeit steht still!\n");
	myqbert.play_sound(6, 0);
}