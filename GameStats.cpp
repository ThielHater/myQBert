#include "GameStats.h"

GameStats::GameStats(void)
{
	Reset();
}

void GameStats::Reset()
{
	Level = 1;
	Round = 1;
	LifeCount = 3;
	Score = 0;
	LastExtraLife = 0;
	TimeFrozen = false;
	QBertHit = false;
	QBertOnDisk = false;
	RoundDone = false;
	ShowSplash = true;
	Pause = false;
	ClearNPC = false;
	FramesLastSpawn = 0;
	FramesTimeFrozen = 0;
	FramesQBertHit = 0;
	FramesQBertOnDisk = 0;
	FramesRoundDone = 0;
	FramesSplashShown = 0;
	FramesPauseChanged = 0;
	BackgroundColor = 0;
	CubeTexIndex = 0;
}