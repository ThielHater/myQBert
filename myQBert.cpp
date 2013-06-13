#include <math.h>
#include <Windows.h>
#include "SpaCE/applikation.h"
#include "Node.h"
#include "AdjacencyList.h"
#include "Cube.h"
#include "QBert.h"
#include "Coily.h"
//#include "dirent.h
#include "resource.h"
#include <fstream>

class spiel : public applikation
{
	private:
		Node nodes[30]; // 28 Würfel und 2 Disks
		Cube cubes[28];
		textur cube_tex[40]; // 36 für Würfel, 4 für Disk
		QBert qbert;
		NPC npc_list; // die gespawnten NPCs werden eingekettet und in der step() Funktion durchlaufen	
		int Level;
		int Round;
		int LifeCount;
		int Score;
		bool timeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen

	public:
		void setup();
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
};

void spiel::setup()
{
	// Variablendeklaration
	textur cube_tex;
	textur qbert_tex;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	float x=0; float y=0; float z=0; float dia=sqrt(50.0f);

	// Titel, Icon und Hintergrundfarbe setzen
	init_window("myQ*Bert", IDI_MYICON, 0, 0, 0);

	// Texturen laden
	cube_tex.load("myQBert/Textures/Cube-L1-R1-1.png");
	qbert_tex.load("myQBert/Textures/QBert-Down-Left.png");

	/*
	DIR *dir = 0; struct dirent *ent = 0; int i=0; char file_path[256]; dir = opendir("myQBert/Textures");
	if (dir)
	{		
		do
		{
			ent = readdir(dir);			
			if (ent && (strcmp(ent->d_name, "Cube") > 0))
			{
				sprintf_s(file_path, "%s/%s", "myQBert/Textures", ent->d_name);
				cube_tex[i].load(file_path);
				i++;
			}
		}
		while (ent);
		closedir (dir);
	}
	*/
	
	// Modell und Textur laden, Reflektionen ausschalten und Objekte positionieren	
	D3DXMatrixRotationY(&rota, D3DX_PI/4.0f);
	for(int i=0; i<28; i++)
	{
		if ((i==7) || (i==13) || (i==18) || (i==22) || (i==25) || (i==27) || (i==28)) { y++; x=y-(y*0.5f); z=y*dia/2; }
		D3DXMatrixTranslation(&trans, x*dia, y*5.0f, z);
		cubes[i].load("Cube.x", "myQBert/Models");
		cubes[i].set_texture(0, &cube_tex);
		cubes[i].disable_reflections();
		cubes[i].add_transform(&rota);
		cubes[i].add_transform(&trans);
		x++;
	}
	D3DXMatrixRotationY(&rota, -D3DX_PI/4.0f);
	D3DXMatrixTranslation(&trans, 3*dia, 15.0f, dia);
	qbert.load("TriPrism.x", "myQBert/Models");
	qbert.disable_reflections();
	qbert.set_texture(0, &qbert_tex);
	qbert.add_transform(&rota);
	qbert.add_transform(&trans);

	// Kamera
	set_perspektive(D3DX_PI/4.0f, 1.0f, 100.0f);
	blickrichtung = D3DXVECTOR3(0, -D3DX_PI/6.0f, 1);
	standort = cubes[19].lookatme(&blickrichtung, 15.0f);
	//standort = D3DXVECTOR3(dia*3.0f, 40, -45);

	// Spiel
	Level = 1;
	Round = 1;
	LifeCount = 3;
	Score = 0;
	timeFrozen = false;

	// Knoten und Kanten aufbauen
	AdjacencyList adjacency_list(29);
	adjacency_list.adj[1].push_back(Node(0, 1));
	adjacency_list.adj[1].push_back(Node(3, 1));
	adjacency_list.adj[1].push_back(Node(2, 1));
	adjacency_list.adj[1].push_back(Node(0, 1));
	adjacency_list.adj[2].push_back(Node(1, 1));
	adjacency_list.adj[2].push_back(Node(5, 1));
	adjacency_list.adj[2].push_back(Node(4, 1));
	adjacency_list.adj[2].push_back(Node(0, 1));
	adjacency_list.adj[3].push_back(Node(0, 1));
	adjacency_list.adj[3].push_back(Node(6, 1));
	adjacency_list.adj[3].push_back(Node(5, 1));
	adjacency_list.adj[3].push_back(Node(1, 1));
	adjacency_list.adj[4].push_back(Node(2, 1));
	adjacency_list.adj[4].push_back(Node(8, 1));
	adjacency_list.adj[4].push_back(Node(7, 1));
	adjacency_list.adj[4].push_back(Node(0, 1));
	adjacency_list.adj[5].push_back(Node(3, 1));
	adjacency_list.adj[5].push_back(Node(9, 1));
	adjacency_list.adj[5].push_back(Node(8, 1));
	adjacency_list.adj[5].push_back(Node(2, 1));
	adjacency_list.adj[6].push_back(Node(0, 1));
	adjacency_list.adj[6].push_back(Node(10, 1));
	adjacency_list.adj[6].push_back(Node(9, 1));
	adjacency_list.adj[6].push_back(Node(3, 1));
	adjacency_list.adj[7].push_back(Node(4, 1));
	adjacency_list.adj[7].push_back(Node(12, 1));
	adjacency_list.adj[7].push_back(Node(11, 1));
	adjacency_list.adj[7].push_back(Node(0, 1));
	adjacency_list.adj[8].push_back(Node(5, 1));
	adjacency_list.adj[8].push_back(Node(13, 1));
	adjacency_list.adj[8].push_back(Node(12, 1));
	adjacency_list.adj[8].push_back(Node(4, 1));
	adjacency_list.adj[9].push_back(Node(6, 1));
	adjacency_list.adj[9].push_back(Node(14, 1));
	adjacency_list.adj[9].push_back(Node(13, 1));
	adjacency_list.adj[9].push_back(Node(5, 1));
	adjacency_list.adj[10].push_back(Node(0, 1));
	adjacency_list.adj[10].push_back(Node(15, 1));
	adjacency_list.adj[10].push_back(Node(14, 1));
	adjacency_list.adj[10].push_back(Node(6, 1));
	adjacency_list.adj[11].push_back(Node(7, 1));
	adjacency_list.adj[11].push_back(Node(17, 1));
	adjacency_list.adj[11].push_back(Node(16, 1));
	adjacency_list.adj[11].push_back(Node(0, 1));
	adjacency_list.adj[12].push_back(Node(8, 1));
	adjacency_list.adj[12].push_back(Node(18, 1));
	adjacency_list.adj[12].push_back(Node(17, 1));
	adjacency_list.adj[12].push_back(Node(7, 1));
	adjacency_list.adj[13].push_back(Node(9, 1));
	adjacency_list.adj[13].push_back(Node(19, 1));
	adjacency_list.adj[13].push_back(Node(18, 1));
	adjacency_list.adj[13].push_back(Node(8, 1));
	adjacency_list.adj[14].push_back(Node(10, 1));
	adjacency_list.adj[14].push_back(Node(20, 1));
	adjacency_list.adj[14].push_back(Node(19, 1));
	adjacency_list.adj[14].push_back(Node(9, 1));
	adjacency_list.adj[15].push_back(Node(0, 1));
	adjacency_list.adj[15].push_back(Node(21, 1));
	adjacency_list.adj[15].push_back(Node(20, 1));
	adjacency_list.adj[15].push_back(Node(10, 1));
	adjacency_list.adj[16].push_back(Node(11, 1));
	adjacency_list.adj[16].push_back(Node(23, 1));
	adjacency_list.adj[16].push_back(Node(22, 1));
	adjacency_list.adj[16].push_back(Node(0, 1));
	adjacency_list.adj[17].push_back(Node(12, 1));
	adjacency_list.adj[17].push_back(Node(24, 1));
	adjacency_list.adj[17].push_back(Node(23, 1));
	adjacency_list.adj[17].push_back(Node(11, 1));
	adjacency_list.adj[18].push_back(Node(13, 1));
	adjacency_list.adj[18].push_back(Node(25, 1));
	adjacency_list.adj[18].push_back(Node(24, 1));
	adjacency_list.adj[18].push_back(Node(12, 1));
	adjacency_list.adj[19].push_back(Node(14, 1));
	adjacency_list.adj[19].push_back(Node(26, 1));
	adjacency_list.adj[19].push_back(Node(25, 1));
	adjacency_list.adj[19].push_back(Node(13, 1));
	adjacency_list.adj[20].push_back(Node(15, 1));
	adjacency_list.adj[20].push_back(Node(27, 1));
	adjacency_list.adj[20].push_back(Node(26, 1));
	adjacency_list.adj[20].push_back(Node(14, 1));
	adjacency_list.adj[21].push_back(Node(0, 1));
	adjacency_list.adj[21].push_back(Node(28, 1));
	adjacency_list.adj[21].push_back(Node(27, 1));
	adjacency_list.adj[21].push_back(Node(15, 1));
	adjacency_list.adj[22].push_back(Node(16, 1));
	adjacency_list.adj[22].push_back(Node(0, 1));
	adjacency_list.adj[22].push_back(Node(0, 1));
	adjacency_list.adj[22].push_back(Node(0, 1));
	adjacency_list.adj[23].push_back(Node(17, 1));
	adjacency_list.adj[23].push_back(Node(0, 1));
	adjacency_list.adj[23].push_back(Node(0, 1));
	adjacency_list.adj[23].push_back(Node(16, 1));
	adjacency_list.adj[24].push_back(Node(18, 1));
	adjacency_list.adj[24].push_back(Node(0, 1));
	adjacency_list.adj[24].push_back(Node(0, 1));
	adjacency_list.adj[24].push_back(Node(17, 1));
	adjacency_list.adj[25].push_back(Node(19, 1));
	adjacency_list.adj[25].push_back(Node(0, 1));
	adjacency_list.adj[25].push_back(Node(0, 1));
	adjacency_list.adj[25].push_back(Node(18, 1));
	adjacency_list.adj[26].push_back(Node(20, 1));
	adjacency_list.adj[26].push_back(Node(0, 1));
	adjacency_list.adj[26].push_back(Node(0, 1));
	adjacency_list.adj[26].push_back(Node(19, 1));
	adjacency_list.adj[27].push_back(Node(21, 1));
	adjacency_list.adj[27].push_back(Node(0, 1));
	adjacency_list.adj[27].push_back(Node(0, 1));
	adjacency_list.adj[27].push_back(Node(20, 1));
	adjacency_list.adj[28].push_back(Node(0, 1));
	adjacency_list.adj[28].push_back(Node(0, 1));
	adjacency_list.adj[28].push_back(Node(0, 1));
	adjacency_list.adj[28].push_back(Node(21, 1));
	
	// Konsole öffnen
	open_console("my*QBert Debug Console");	

	/*
	// Coily Test
	Coily c(2);

	for (int i=0; i<30; i++)
		printf("Coily: %d", c.Step(adjacency_list, 28));
	*/
}

int spiel::step()
{
	return 0;
}

int spiel::render()
{
	for(int i=0;i<28;i++)
		cubes[i].render(0, RENDER_OPAQUE);
	qbert.render(1, RENDER_ALL);
	return 1;
}

spiel myQBert;