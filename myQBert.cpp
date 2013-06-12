#include <math.h>
#include <Windows.h>
#include "SpaCE/applikation.h"
#include "Node.h"
#include "Cube.h"
#include "QBert.h"
//#include "dirent.h
#include "resource.h"

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
	int Level = 1;
	int Round = 1;
	int LifeCount = 3;
	int Points = 0;
	bool timeFrozen = false;
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