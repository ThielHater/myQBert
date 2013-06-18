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

int GameStats::GetLevel(void)
{
	return Level;
}

int GameStats::GetRound(void)
{
	return Round;
}

int GameStats::GetLifeCount(void)
{
	return LifeCount;
}

int GameStats::GetScore(void)
{
	return Score;
}

int GameStats::AddLevel(void)
{
	Level++;
	return Level;
}

int GameStats::AddRound(void)
{
	Round++;
	return Round;
}

int GameStats::SubLifeCount(void)
{
	LifeCount--;
	return LifeCount;
}

int GameStats::AddScore(int Scr)
{
	Score += Scr;
	return Score;
}