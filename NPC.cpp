#include "NPC.h"

NPC::NPC(void)
{
	frames_per_jump = 5; // verschiedene Gegner / Qbert selbst haben unterschiedliche Geschwindigkeiten?
}

NPC::~NPC(void)
{
}

void NPC::move(npc_direction direction) {
	if (!is_moving) {
		is_moving = true;
		move_direction = direction;
	}
}

int NPC::Step()
{
	if (!is_moving)
		return 0;

	enum first_move_e { MOVE_Y, MOVE_XZ };

	// Wenn wir nach unten springen, erst über die XZ Achse bewegen, sonst erst über die Y Achse
	first_move_e first_move = (move_direction == DIR_LEFTDOWN || move_direction == DIR_RIGHTDOWN) ? MOVE_XZ : MOVE_Y;

	static int moved_sum = 0;
	static bool first_move_done = false;

	D3DXMATRIX tr;
	float sx = sqrt(50.0f) / 2 / frames_per_jump; // halbe Diagonale
	float sz = sx;
	float sy = 5.0f / frames_per_jump; // Seitenlänge
		
	// über Y-Achse bewegen
	if (first_move == MOVE_Y && !first_move_done || first_move == MOVE_XZ && first_move_done) {
		if (move_direction == DIR_LEFTDOWN || move_direction == DIR_RIGHTDOWN)
			D3DXMatrixTranslation(&tr, 0, -sy, 0);
		else
			D3DXMatrixTranslation(&tr, 0, sy, 0);
	}
	// über XZ-Achse bewegen
	else {
		if (move_direction == DIR_LEFTDOWN)
			D3DXMatrixTranslation(&tr, -sx, 0, -sz);
		else if (move_direction == DIR_LEFTUP)
			D3DXMatrixTranslation(&tr, -sx, 0, sz);
		else if (move_direction == DIR_RIGHTDOWN)
			D3DXMatrixTranslation(&tr, sx, 0, -sz);
		else if (move_direction == DIR_RIGHTUP)
			D3DXMatrixTranslation(&tr, sx, 0, sz);
	}

	// Bewegung fertig?
	if (moved_sum >= frames_per_jump) {
		if (first_move_done) {
			is_moving = false;
			first_move_done = false;
		}
		else {
			first_move_done = true;
		}

		moved_sum = 0;
		return 0;
	}

	add_transform(&tr);
	moved_sum++;

	return 0;
}


int NPC::Collision(void)
{
	return 0;
}

int NPC::NodeEffect(void)
{
	return 0;
}