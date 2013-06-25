#include "RedBall.h"
#include "Ball.h"
#include "Node.h"

RedBall::RedBall(Node ArgCurNode) : Ball(ArgCurNode, RED, "Red-Ball")
{
}

void RedBall::Collision(GameStats &stats)
{
	stats.LifeCount--;
	stats.QBertHit = true;
	if (stats.LifeCount > 0)
		printf("Q*Bert wurde vom roten Ball getroffen, noch %d Leben!\n", stats.LifeCount);
	else
		printf("Q*Bert wurde vom roten Ball getroffen, kein Leben mehr!\n", stats.LifeCount);
}