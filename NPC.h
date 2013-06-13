#pragma once
#include "SpaCE\objekt.h"
#include "Node.h"

class NPC : public objekt
{
	/*
		Pierre: Sollten wir die Kollisionen räumlich prüfen oder anhand der Knoten?
	*/

	public:
		NPC(void);
		~NPC(void);		
		int CurNode; // Knoten, auf dem der NPC steht
		textur *TexNormal; // Textur, wenn der NPC auf einem Feld steht
		textur *TexJump; // Textur, wenn der NPC springt
		virtual int Step(void); // bewegt den NPC, prüft Kollisionen, kümmert sich um Feldeffekte
		virtual int Collision(void); // wird aufgerufen, wenn eine Kollision aufgetreten ist
		virtual int NodeEffect(void); // wird aufgerufen, wenn der NPC auf ein Feld kommt		
};