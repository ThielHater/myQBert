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
		int FramesLastSpawn;
		int FramesTimeFrozen;
		bool TimeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen
		bool QBertHit; // in Step() setzen, in myQBert.cpp abfragen!
		void Reset();
};