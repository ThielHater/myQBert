#pragma once
#include "SpaCE\objekt.h"
#include "GameStats.h"
#include "Node.h"
#include "AdjacencyList.h"

enum DirectionEnum { DIR_NONE, DIR_LEFTDOWN, DIR_LEFTUP, DIR_RIGHTDOWN, DIR_RIGHTUP };

class NPC : public objekt
{
	public:
		NPC(Node ArgCurNode);		
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
		virtual void InitGraphics(char *TexName) = 0; // Modell und Texturen laden
		virtual void Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node); // bewegt den NPC, prüft Kollisionen, kümmert sich um Feldeffekte
		virtual void Collision(GameStats &stats) = 0; // wird aufgerufen, wenn eine Kollision aufgetreten ist
		virtual void NodeEffect(GameStats &stats) {} // wird aufgerufen, wenn der NPC auf ein Feld kommt
		virtual void SetTexture(void) = 0; // Allgemein
};