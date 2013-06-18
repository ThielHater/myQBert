#pragma once

class GameStats
{
	public:
		GameStats(void);
		~GameStats(void);
		int Level;
		int Round;
		int LifeCount;
		int Score;
		bool TimeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen
};