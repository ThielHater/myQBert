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
		void Move(DirectionEnum direction); // NPC räumlich in eine bestimmte Richtung bewegen
		virtual void InitGraphics(char *TexName); // Modell und Texturen laden
		virtual void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_node); // bewegt den NPC, prüft Kollisionen, kümmert sich um Feldeffekte
		virtual void Collision(void); // wird aufgerufen, wenn eine Kollision aufgetreten ist
		virtual void NodeEffect(void); // wird aufgerufen, wenn der NPC auf ein Feld kommt
		virtual void SetTexture(void); // Allgemein
};