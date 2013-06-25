#include "SpaCE/applikation.h"
#include "AdjacencyList.h"
#include "Cube.h"
#include "QBert.h"
#include "GameStats.h"

class MyQBert : public applikation
{
	private:
		static MyQBert *instance;
		AdjacencyList adjacency_list; // 31 = 1 Abgrund + 28 Würfel + 2 Disks
		Cube cubes[29]; // 29 = 1 Abgrund + 28 Würfel
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

	public:
		MyQBert();
		static void playSound(int i, int loop = 0);
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