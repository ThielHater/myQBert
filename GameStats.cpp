#include "GameStats.h"

GameStats::GameStats(void)
{
	Level = 1;
	Round = 1;
	LifeCount = 3;
	Score = 0;
	TimeFrozen = false;
}

GameStats::~GameStats(void)
{
}