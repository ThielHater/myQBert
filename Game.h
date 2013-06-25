#include "SpaCE/applikation.h"
#include "Cube.h"
#include "GameStats.h"
#include "AdjacencyList.h"
#include "NPC.h"
#include "QBert.h"

class Game : public applikation
{
	private:
		AdjacencyList adjacency_list; // 31 = 1 Abgrund + 28 W�rfel + 2 Disks
		Cube cubes[29]; // 29 = 1 Abgrund + 28 W�rfel
		Cube disks[2];
		textur cube_tex[3]; // werden jede Runde neu geladen!
		textur disk_tex[4];
		QBert *qbert;
		std::vector<NPC*> npc_list; // die gespawnten NPCs werden eingekettet und in der step() Funktion aufgerufen
		GameStats stats;
		sprite digit_sprite[10];
		sprite player_sprite;
		sprite lvl_sprite;
		sprite rnd_sprite;
		sprite life_sprite;
		sprite splash_sprite[3];
		int frame_rate;

	public:
		Game(int ArgAdjCount) : adjacency_list(ArgAdjCount) { }
		void window_init(char *txt, WORD icon_num, int r, int g, int b);
		void window_mode(char *txt, bool window);
		void load_cube_tex();
		bool check_round();
		void new_round();
		void qbert_hit();
		void reset();
		void game_over();
		void setup();
		void setup_nodes();
		void step();
		void render_sprites();
		int render();
};