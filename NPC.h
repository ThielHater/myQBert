#pragma once
#include "SpaCE\objekt.h"
#include "Node.h"

class NPC : public objekt
{
	/*
		Pierre: Sollten wir die Kollisionen räumlich prüfen oder anhand der Knoten?
	*/
	public:
		enum npc_direction {
				DIR_LEFTDOWN,
				DIR_LEFTUP,
				DIR_RIGHTDOWN,
				DIR_RIGHTUP
			};

	private:
		bool is_moving;
		npc_direction move_direction;
		int frames_per_jump; // Wieviele Frames ein Sprung dauert bzw. die Geschwindigkeit der Sprung-Bewegung. Je kleiner, desto schneller.

	public:
		NPC(void);
		~NPC(void);		
		int CurNode; // Knoten, auf dem der NPC steht
		textur *TexNormal; // Textur, wenn der NPC auf einem Feld steht
		textur *TexJump; // Textur, wenn der NPC springt
		virtual int Step(void); // bewegt den NPC, prüft Kollisionen, kümmert sich um Feldeffekte
		virtual int Collision(void); // wird aufgerufen, wenn eine Kollision aufgetreten ist
		virtual int NodeEffect(void); // wird aufgerufen, wenn der NPC auf ein Feld kommt		
		void NPC::move(npc_direction direction); // NPC in eine bestimmte Richtung bewegen
};