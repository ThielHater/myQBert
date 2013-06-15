#pragma once
#include "SpaCE\objekt.h"
#include "AdjacencyList.h"
#include "Node.h"

enum DirectionEnum { DIR_NONE, DIR_LEFTDOWN, DIR_LEFTUP, DIR_RIGHTDOWN, DIR_RIGHTUP };

class NPC : public objekt
{
	public:
		NPC(void);
		NPC(Node ArgCurNode);
		void InitGraphics(char *ArgTexName);
		~NPC(void);		
		bool isMoving; // verschiedene NPCs haben unterschiedliche Geschwindigkeiten
		DirectionEnum MoveDirection;
		int FramesPerJump; // Wieviele Frames ein Sprung dauert bzw. die Geschwindigkeit der Sprung-Bewegung. Je kleiner, desto schneller.
		Node CurNode; // Knoten, auf dem der NPC steht
		textur TexDownLeft; // Textur, wenn der NPC auf einem Feld steht
		textur TexDownLeftJump; // Textur, wenn der NPC auf einem Feld steht
		textur TexDownRight; // Textur, wenn der NPC auf einem Feld steht
		textur TexDownRightJump; // Textur, wenn der NPC auf einem Feld steht
		textur TexUpLeft; // Textur, wenn der NPC springt
		textur TexUpLeftJump; // Textur, wenn der NPC springt
		textur TexUpRight; // Textur, wenn der NPC springt
		textur TexUpRightJump; // Textur, wenn der NPC springt
		virtual int Step(const AdjacencyList &adjacency_list); // bewegt den NPC, prüft Kollisionen, kümmert sich um Feldeffekte
		void Move(DirectionEnum direction); // NPC in eine bestimmte Richtung bewegen	
		virtual int Collision(void); // wird aufgerufen, wenn eine Kollision aufgetreten ist
		virtual int NodeEffect(void); // wird aufgerufen, wenn der NPC auf ein Feld kommt		
};