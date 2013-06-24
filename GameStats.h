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
		int FramesQBertHit;
		int FramesRoundDone;
		int FramesSplashShown;
		bool TimeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen
		bool QBertHit;
		bool RoundDone;
		bool ShowSplash;
		void Reset();
};