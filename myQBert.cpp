#include <Windows.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <list>
#include <vector>
#include <sstream>
#include <string>
#include "SpaCE/applikation.h"
#include "GameStats.h"
#include "Edge.h"
#include "Node.h"
#include "AdjacencyList.h"
#include "Cube.h"
#include "QBert.h"
#include "Coily.h"
#include "SlickSam.h"
#include "UggWrongWay.h"
#include "resource.h"

class spiel : public applikation
{
	private:
		AdjacencyList adjacency_list; // 1 NULL, 28 Würfel, 2 Disks
		Cube cubes[28];
		Cube disks[2];
		textur cube_tex[3]; // werden jede Runde neu geladen
		textur disk_tex[4];
		QBert qbert;
		std::list<NPC*> npc_list; // die gespawnten NPCs werden eingekettet und in der step() Funktion aufgerufen
		GameStats stats;
		float cam_abstand;

	public:
		spiel(int ArgAdjCount) : adjacency_list(ArgAdjCount) { }
		void setup();
		void reset();
		int step();		
		int render();

		void init_window(char *txt, WORD icon_num, int r, int g, int b)
		{
			set_title(txt);
			HWND handle = FindWindow(NULL, _TEXT(txt));
			const HICON icon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(icon_num));
			if (icon)
			{
				SendMessage(handle, WM_SETICON, ICON_BIG, (LPARAM)icon);
				SendMessage(handle, WM_SETICON, ICON_SMALL, (LPARAM)icon);
			}
			set_bkcolor(r, g, b);
		}

		void load_cube_tex()
		{
			std::stringstream ss;
			for (int i=0; i<3; i++)
			{
				ss <<"myQBert/Textures/Cube-L" <<stats.GetLevel() <<"-R" <<stats.GetRound() <<"-" <<(i+1) <<".png";
				cube_tex[i].load((char*)ss.str().c_str());
				ss.str(std::string()); ss.clear();
			}
		}
};

void spiel::setup()
{
	// Variablendeklaration
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	int l=6;
	float dia=sqrt(50.0f);
	float x=l/2.0f*dia;
	float y=l*5.0f;
	float z=l*dia/2.0f;

	// Titel, Icon und Hintergrundfarbe setzen
	init_window("myQ*Bert", IDI_MYICON, 0, 0, 0);

	// Disk Texturen laden
	disk_tex[0].load("myQBert/Textures/Disk-1.png");
	disk_tex[1].load("myQBert/Textures/Disk-2.png");
	disk_tex[2].load("myQBert/Textures/Disk-3.png");
	disk_tex[3].load("myQBert/Textures/Disk-4.png");

	// Modell und Textur der Würfel laden, Reflektionen ausschalten und Würfel positionieren
	load_cube_tex();
	D3DXMatrixRotationY(&rota, D3DX_PI/4.0f);
	for(int i=1; i<=28; i++)
	{
		if ((i==2) || (i==4) || (i==7) || (i==11) || (i==16) || (i==22))
		{
			l--;
			x=l/2.0f*dia;
			y=l*5.0f;
			z=l*dia/2.0f;
		}
		D3DXMatrixTranslation(&trans, x, y, z);
		cubes[i].load("Cube.x", "myQBert/Models");
		cubes[i].init_texture(cube_tex);
		cubes[i].disable_reflections();
		cubes[i].add_transform(&rota);
		cubes[i].add_transform(&trans);
		x+=dia;
	}

	// Kamera
	cam_abstand = 15.0f;
	set_perspektive(D3DX_PI/4.0f, 1.0f, 1000.0f);
	blickrichtung = D3DXVECTOR3(0, -D3DX_PI/6.0f, 1.0f);
	standort = cubes[8].lookatme(&blickrichtung, cam_abstand);
	set_sunlight(0, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.0f);

	// zufällige Zufallszahlen :)
	srand((long)time(NULL));

	// Knoten und Kanten aufbauen
	adjacency_list[0].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[1].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[1].push_back(Edge(Node(3, &cubes[3]), 1));
	adjacency_list[1].push_back(Edge(Node(2, &cubes[2]), 1));
	adjacency_list[1].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[2].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[2].push_back(Edge(Node(5, &cubes[5]), 1));
	adjacency_list[2].push_back(Edge(Node(4, &cubes[4]), 1));
	adjacency_list[2].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[3].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[3].push_back(Edge(Node(6, &cubes[6]), 1));
	adjacency_list[3].push_back(Edge(Node(5, &cubes[5]), 1));
	adjacency_list[3].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[4].push_back(Edge(Node(2, &cubes[2]), 1));
	adjacency_list[4].push_back(Edge(Node(8, &cubes[8]), 1));
	adjacency_list[4].push_back(Edge(Node(7, &cubes[7]), 1));
	adjacency_list[4].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[5].push_back(Edge(Node(3, &cubes[3]), 1));
	adjacency_list[5].push_back(Edge(Node(9, &cubes[9]), 1));
	adjacency_list[5].push_back(Edge(Node(8, &cubes[8]), 1));
	adjacency_list[5].push_back(Edge(Node(2, &cubes[2]), 1));
	adjacency_list[6].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[6].push_back(Edge(Node(10, &cubes[10]), 1));
	adjacency_list[6].push_back(Edge(Node(9, &cubes[9]), 1));
	adjacency_list[6].push_back(Edge(Node(3, &cubes[3]), 1));
	adjacency_list[7].push_back(Edge(Node(4, &cubes[4]), 1));
	adjacency_list[7].push_back(Edge(Node(12, &cubes[12]), 1));
	adjacency_list[7].push_back(Edge(Node(11, &cubes[11]), 1));
	adjacency_list[7].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[8].push_back(Edge(Node(5, &cubes[5]), 1));
	adjacency_list[8].push_back(Edge(Node(13, &cubes[13]), 1));
	adjacency_list[8].push_back(Edge(Node(12, &cubes[12]), 1));
	adjacency_list[8].push_back(Edge(Node(4, &cubes[4]), 1));
	adjacency_list[9].push_back(Edge(Node(6, &cubes[6]), 1));
	adjacency_list[9].push_back(Edge(Node(14, &cubes[14]), 1));
	adjacency_list[9].push_back(Edge(Node(13, &cubes[13]), 1));
	adjacency_list[9].push_back(Edge(Node(5, &cubes[5]), 1));
	adjacency_list[10].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[10].push_back(Edge(Node(15, &cubes[15]), 1));
	adjacency_list[10].push_back(Edge(Node(14, &cubes[14]), 1));
	adjacency_list[10].push_back(Edge(Node(6, &cubes[6]), 1));
	adjacency_list[11].push_back(Edge(Node(7, &cubes[7]), 1));
	adjacency_list[11].push_back(Edge(Node(17, &cubes[17]), 1));
	adjacency_list[11].push_back(Edge(Node(16, &cubes[16]), 1));
	adjacency_list[11].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[12].push_back(Edge(Node(8, &cubes[8]), 1));
	adjacency_list[12].push_back(Edge(Node(18, &cubes[18]), 1));
	adjacency_list[12].push_back(Edge(Node(17, &cubes[17]), 1));
	adjacency_list[12].push_back(Edge(Node(7, &cubes[7]), 1));
	adjacency_list[13].push_back(Edge(Node(9, &cubes[9]), 1));
	adjacency_list[13].push_back(Edge(Node(19, &cubes[19]), 1));
	adjacency_list[13].push_back(Edge(Node(18, &cubes[18]), 1));
	adjacency_list[13].push_back(Edge(Node(8, &cubes[8]), 1));
	adjacency_list[14].push_back(Edge(Node(10, &cubes[10]), 1));
	adjacency_list[14].push_back(Edge(Node(20, &cubes[20]), 1));
	adjacency_list[14].push_back(Edge(Node(19, &cubes[19]), 1));
	adjacency_list[14].push_back(Edge(Node(9, &cubes[9]), 1));
	adjacency_list[15].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[15].push_back(Edge(Node(21, &cubes[21]), 1));
	adjacency_list[15].push_back(Edge(Node(20, &cubes[20]), 1));
	adjacency_list[15].push_back(Edge(Node(10, &cubes[10]), 1));
	adjacency_list[16].push_back(Edge(Node(11, &cubes[11]), 1));
	adjacency_list[16].push_back(Edge(Node(23, &cubes[23]), 1));
	adjacency_list[16].push_back(Edge(Node(22, &cubes[22]), 1));
	adjacency_list[16].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[17].push_back(Edge(Node(12, &cubes[12]), 1));
	adjacency_list[17].push_back(Edge(Node(24, &cubes[24]), 1));
	adjacency_list[17].push_back(Edge(Node(23, &cubes[23]), 1));
	adjacency_list[17].push_back(Edge(Node(11, &cubes[11]), 1));
	adjacency_list[18].push_back(Edge(Node(13, &cubes[13]), 1));
	adjacency_list[18].push_back(Edge(Node(25, &cubes[25]), 1));
	adjacency_list[18].push_back(Edge(Node(24, &cubes[24]), 1));
	adjacency_list[18].push_back(Edge(Node(12, &cubes[12]), 1));
	adjacency_list[19].push_back(Edge(Node(14, &cubes[14]), 1));
	adjacency_list[19].push_back(Edge(Node(26, &cubes[26]), 1));
	adjacency_list[19].push_back(Edge(Node(25, &cubes[25]), 1));
	adjacency_list[19].push_back(Edge(Node(13, &cubes[13]), 1));
	adjacency_list[20].push_back(Edge(Node(15, &cubes[15]), 1));
	adjacency_list[20].push_back(Edge(Node(27, &cubes[27]), 1));
	adjacency_list[20].push_back(Edge(Node(26, &cubes[26]), 1));
	adjacency_list[20].push_back(Edge(Node(14, &cubes[14]), 1));
	adjacency_list[21].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[21].push_back(Edge(Node(28, &cubes[28]), 1));
	adjacency_list[21].push_back(Edge(Node(27, &cubes[27]), 1));
	adjacency_list[21].push_back(Edge(Node(15, &cubes[15]), 1));
	adjacency_list[22].push_back(Edge(Node(16, &cubes[16]), 1));
	adjacency_list[22].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[22].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[22].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[23].push_back(Edge(Node(17, &cubes[17]), 1));
	adjacency_list[23].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[23].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[23].push_back(Edge(Node(16, &cubes[16]), 1));
	adjacency_list[24].push_back(Edge(Node(18, &cubes[18]), 1));
	adjacency_list[24].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[24].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[24].push_back(Edge(Node(17, &cubes[17]), 1));
	adjacency_list[25].push_back(Edge(Node(19, &cubes[19]), 1));
	adjacency_list[25].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[25].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[25].push_back(Edge(Node(18, &cubes[18]), 1));
	adjacency_list[26].push_back(Edge(Node(20, &cubes[20]), 1));
	adjacency_list[26].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[26].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[26].push_back(Edge(Node(19, &cubes[19]), 1));
	adjacency_list[27].push_back(Edge(Node(21, &cubes[21]), 1));
	adjacency_list[27].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[27].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[27].push_back(Edge(Node(20, &cubes[20]), 1));
	adjacency_list[28].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[28].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[28].push_back(Edge(Node(0, &cubes[0]), 1));
	adjacency_list[28].push_back(Edge(Node(21, &cubes[21]), 1));

	// Konsole öffnen
	open_console("myQ*Bert Debug Console");

	// Q*Bert und Coily spawnen
	QBert *q = new QBert(Node(1, &cubes[1]));
	qbert = *q;
	Coily *c = new Coily(Node(2, &cubes[2]));
	npc_list.push_back(c);
}

void spiel::reset()
{
	npc_list.clear();

	qbert.Reset(Node(1, &cubes[1]));
	
	for (int i=1; i<=28; i++)
	{
		cubes[i].cur = 0;
		cubes[i].update_texture();
	}	

	Coily *c = new Coily(Node(1, &cubes[1]));
	npc_list.push_back(c);

	stats.Reset();
}

int spiel::step()
{
	// Variablen
	unsigned char keys[256];
	DIMOUSESTATE mouse;

	bool levelComplete = true;
	for (int i=1; i<=28; i++)
	{
		if (cubes[i].cur != 2)
		{
			levelComplete = false;
			break;
		}
	}

	// Alle Würfel fertig, Level abgeschlossen
	if (levelComplete)
	{
		reset();
		return 1;
	}

	for(std::list<NPC*>::iterator it = npc_list.begin(); it != npc_list.end(); ++it)
	{
		(*it)->Step(adjacency_list, stats, qbert.CurNode);
	}

	// Game Over
	if (stats.GetLifeCount() == 0)
	{
		reset();
		return 1;
	}

	if (poll_keyboard(keys))
	{
		// Q*Bert Steuerung
		if (keys[DIK_RIGHT])
			qbert.Step(adjacency_list, stats, DIR_RIGHTDOWN);
		else if (keys[DIK_LEFT])
			qbert.Step(adjacency_list, stats, DIR_LEFTUP);
		else if (keys[DIK_UP])
			qbert.Step(adjacency_list, stats, DIR_RIGHTUP);
		else if (keys[DIK_DOWN])
			qbert.Step(adjacency_list, stats, DIR_LEFTDOWN);
		else
			qbert.Step(adjacency_list, stats, DIR_NONE);

		// Zoom
		if (keys[DIK_ADD])
			cam_abstand -= 1.0f;
		else if (keys[DIK_SUBTRACT])
			cam_abstand += 1.0f;
	}

	// Blickrichtung
	if (poll_mouse(&mouse) && mouse.rgbButtons[1])
	{
		blickrichtung.x += mouse.lX / 100.0f;
		blickrichtung.y -= mouse.lY / 100.0f;
	}

	// Kamera aktualisieren
	standort = cubes[8].lookatme(&blickrichtung, cam_abstand);

	return 1;
}

int spiel::render()
{
	// Elemente auf dem Spielfeld berechnen
	step();

	// Würfel rendern
	for(int i=1;i<=28;i++)
		cubes[i].render(0, RENDER_OPAQUE);

	// Q*Bert rendern
	qbert.render(1, RENDER_ALL);

	// NPCs rendern
	for(std::list<NPC*>::iterator it = npc_list.begin(); it != npc_list.end(); ++it)
		(*it)->render(1, RENDER_ALL);

	return 1;
}

spiel myQBert(31);