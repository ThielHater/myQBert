#pragma once

class GameStats
{
	private:
		int Level;
		int Round;
		int LifeCount;
		int Score;
		bool TimeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen

	public:
		GameStats(void);
		~GameStats(void);
		int GetLevel(void);
		int GetRound(void);
		int GetLifeCount(void);
		int GetScore(void);
		int AddLevel(void);
		int AddRound(void);
		int SubLifeCount(void);
		int AddScore(int);
};