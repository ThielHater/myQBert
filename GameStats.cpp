#include "GameStats.h"

GameStats::GameStats(void)
{
	Reset();
}

GameStats::~GameStats(void)
{
}

void GameStats::Reset()
{
	Level = 1;
	Round = 1;
	LifeCount = 3;
	Score = 0;
	TimeFrozen = false;
	QBertHit = false;
	RoundDone = false;
	ShowSplash = true;
	FramesLastSpawn = 0;
	FramesTimeFrozen = 0;
	FramesQBertHit = 0;
	FramesRoundDone = 0;
	FramesSplashShown = 0;
}