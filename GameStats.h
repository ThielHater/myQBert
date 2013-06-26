#pragma once

class GameStats
{
	public:
		GameStats(void);
		int Level;
		int Round;
		int LifeCount;
		int Score;
		int FramesLastSpawn;
		int FramesTimeFrozen;
		int FramesQBertHit;
		int FramesQBertOnDisk;
		int FramesRoundDone;
		int FramesSplashShown;
		int FramesPauseChanged;
		bool TimeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen
		bool QBertHit;
		bool QBertOnDisk;
		bool RoundDone;
		bool ShowSplash;
		bool Pause;
		void Reset();
};