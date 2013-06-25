#include "GreenBall.h"
#include "Node.h"
#include "Ball.h"

GreenBall::GreenBall(Node ArgCurNode) : Ball(ArgCurNode, GREEN, "Green-Ball") {}

void GreenBall::Collision(GameStats &stats) {
	stats.TimeFrozen = true;
	stats.Score += 100;
	printf("Q*Bert hat den gr\fcnen Ball gefangen, die Zeit steht still!\n");
}