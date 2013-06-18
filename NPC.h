#pragma once
#include "SpaCE\objekt.h"
#include "GameStats.h"
#include "Node.h"
#include "AdjacencyList.h"

enum DirectionEnum { DIR_NONE, DIR_LEFTDOWN, DIR_LEFTUP, DIR_RIGHTDOWN, DIR_RIGHTUP };

class NPC : public objekt
{
	public:
		NPC(void);
		NPC(Node ArgCurNode);
		void InitGraphics(char *ArgTexName);
		~NPC(void);
		bool isMoving; // Bewegt sich der NPC?
		bool isWaiting; // Wartet der NPC?
		bool FirstMoveDone;
		DirectionEnum MoveDirection; // aktuelle Richtung
		int FramesPerJump; // Anzahl der Frames, die ein Sprung dauert -> umso kleiner, desto schneller
		int FramesPerWait; // Anzahl der Frames, die der NPC warten muss
		int FramesJumped;
		int FramesWaited;
		Node CurNode; // Knoten, auf dem der NPC steht
		Node TargetNode; // nächster Knoten
		textur TexDownLeft; // Textur, wenn der NPC auf einem Feld steht
		textur TexDownLeftJump; // Textur, wenn der NPC auf einem Feld steht
		textur TexDownRight; // Textur, wenn der NPC auf einem Feld steht
		textur TexDownRightJump; // Textur, wenn der NPC auf einem Feld steht
		textur TexUpLeft; // Textur, wenn der NPC springt
		textur TexUpLeftJump; // Textur, wenn der NPC springt
		textur TexUpRight; // Textur, wenn der NPC springt
		textur TexUpRightJump; // Textur, wenn der NPC springt
		void Move(DirectionEnum direction); // NPC räumlich in eine bestimmte Richtung bewegen
		virtual int SetTexture(void); // Allgemein
		virtual int Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // bewegt den NPC, prüft Kollisionen, kümmert sich um Feldeffekte
		virtual int Collision(void); // wird aufgerufen, wenn eine Kollision aufgetreten ist
		virtual int NodeEffect(void); // wird aufgerufen, wenn der NPC auf ein Feld kommt
};