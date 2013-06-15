#include <math.h>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <list>
#include "SpaCE/applikation.h"
#include "Edge.h"
#include "Node.h"
#include "AdjacencyList.h"
#include "Cube.h"
#include "QBert.h"
#include "Coily.h"
//#include "dirent.h
#include "resource.h"

using namespace std;

class spiel : public applikation
{	
	private:		
		AdjacencyList adjacency_list; // 1 NULL, 28 Würfel, 2 Disks
		Cube cubes[31]; // siehe oben
		textur cube_tex[40]; // 36 Würfel, 4 Disks
		QBert qbert;	
		list<NPC> npc_list; // die gespawnten NPCs werden eingekettet und in der step() Funktion durchlaufen	
		int Level;
		int Round;
		int Points;
		int LifeCount;
		int Score;
		bool timeFrozen; // Zeit wird pausiert, nur Q*Bert kann sich bewegen
		float cam_abstand;	

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
		D3DXMATRIX getTransOfCube(int cube)
		{
			D3DXMATRIX m;
			cubes[cube].get_transform(&m);
			return m;
		}

};

void spiel::setup()
{
	// Variablendeklaration
	textur cube_tex;
	textur qbert_tex;	
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	int l=6;
	float dia=sqrt(50.0f);
	float x=l/2.0f*dia;
	float y=l*5.0f;
	float z=l*dia/2.0f;

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
	D3DXMATRIX m;
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
		cubes[i].set_texture(0, &cube_tex);
		cubes[i].disable_reflections();
		cubes[i].add_transform(&rota);
		cubes[i].add_transform(&trans);
		if (i==2)
			cubes[i].get_transform(&m);
		x+=dia;
	}
	D3DXMatrixRotationY(&rota, -D3DX_PI/4.0f);
	D3DXMatrixTranslation(&trans, 3.0f*dia, 15.0f, dia);
	qbert.load("TriPrism.x", "myQBert/Models");
	qbert.disable_reflections();
	qbert.set_texture(0, &qbert_tex);
	qbert.add_transform(&rota);
	qbert.add_transform(&trans);

	// Kamera
	cam_abstand = 15.0f;
	set_perspektive(D3DX_PI/4.0f, 1.0f, 1000.0f);
	blickrichtung = D3DXVECTOR3(0, -D3DX_PI/6.0f, 1);
	standort = cubes[8].lookatme(&blickrichtung, cam_abstand);

	// Spiel
	Level = 1;
	Round = 1;
	LifeCount = 3;
	Score = 0;
	timeFrozen = false;

	// Knoten und Kanten aufbauen	
	AdjacencyList adjacency_list(31);
	adjacency_list[0].push_back(Edge(0, 1));
	adjacency_list[1].push_back(Edge(0, 1));
	adjacency_list[1].push_back(Edge(3, 1));
	adjacency_list[1].push_back(Edge(2, 1));
	adjacency_list[1].push_back(Edge(0, 1));
	adjacency_list[2].push_back(Edge(1, 1));
	adjacency_list[2].push_back(Edge(5, 1));
	adjacency_list[2].push_back(Edge(4, 1));
	adjacency_list[2].push_back(Edge(0, 1));
	adjacency_list[3].push_back(Edge(0, 1));
	adjacency_list[3].push_back(Edge(6, 1));
	adjacency_list[3].push_back(Edge(5, 1));
	adjacency_list[3].push_back(Edge(1, 1));
	adjacency_list[4].push_back(Edge(2, 1));
	adjacency_list[4].push_back(Edge(8, 1));
	adjacency_list[4].push_back(Edge(7, 1));
	adjacency_list[4].push_back(Edge(0, 1));
	adjacency_list[5].push_back(Edge(3, 1));
	adjacency_list[5].push_back(Edge(9, 1));
	adjacency_list[5].push_back(Edge(8, 1));
	adjacency_list[5].push_back(Edge(2, 1));
	adjacency_list[6].push_back(Edge(0, 1));
	adjacency_list[6].push_back(Edge(10, 1));
	adjacency_list[6].push_back(Edge(9, 1));
	adjacency_list[6].push_back(Edge(3, 1));
	adjacency_list[7].push_back(Edge(4, 1));
	adjacency_list[7].push_back(Edge(12, 1));
	adjacency_list[7].push_back(Edge(11, 1));
	adjacency_list[7].push_back(Edge(0, 1));
	adjacency_list[8].push_back(Edge(5, 1));
	adjacency_list[8].push_back(Edge(13, 1));
	adjacency_list[8].push_back(Edge(12, 1));
	adjacency_list[8].push_back(Edge(4, 1));
	adjacency_list[9].push_back(Edge(6, 1));
	adjacency_list[9].push_back(Edge(14, 1));
	adjacency_list[9].push_back(Edge(13, 1));
	adjacency_list[9].push_back(Edge(5, 1));
	adjacency_list[10].push_back(Edge(0, 1));
	adjacency_list[10].push_back(Edge(15, 1));
	adjacency_list[10].push_back(Edge(14, 1));
	adjacency_list[10].push_back(Edge(6, 1));
	adjacency_list[11].push_back(Edge(7, 1));
	adjacency_list[11].push_back(Edge(17, 1));
	adjacency_list[11].push_back(Edge(16, 1));
	adjacency_list[11].push_back(Edge(0, 1));
	adjacency_list[12].push_back(Edge(8, 1));
	adjacency_list[12].push_back(Edge(18, 1));
	adjacency_list[12].push_back(Edge(17, 1));
	adjacency_list[12].push_back(Edge(7, 1));
	adjacency_list[13].push_back(Edge(9, 1));
	adjacency_list[13].push_back(Edge(19, 1));
	adjacency_list[13].push_back(Edge(18, 1));
	adjacency_list[13].push_back(Edge(8, 1));
	adjacency_list[14].push_back(Edge(10, 1));
	adjacency_list[14].push_back(Edge(20, 1));
	adjacency_list[14].push_back(Edge(19, 1));
	adjacency_list[14].push_back(Edge(9, 1));
	adjacency_list[15].push_back(Edge(0, 1));
	adjacency_list[15].push_back(Edge(21, 1));
	adjacency_list[15].push_back(Edge(20, 1));
	adjacency_list[15].push_back(Edge(10, 1));
	adjacency_list[16].push_back(Edge(11, 1));
	adjacency_list[16].push_back(Edge(23, 1));
	adjacency_list[16].push_back(Edge(22, 1));
	adjacency_list[16].push_back(Edge(0, 1));
	adjacency_list[17].push_back(Edge(12, 1));
	adjacency_list[17].push_back(Edge(24, 1));
	adjacency_list[17].push_back(Edge(23, 1));
	adjacency_list[17].push_back(Edge(11, 1));
	adjacency_list[18].push_back(Edge(13, 1));
	adjacency_list[18].push_back(Edge(25, 1));
	adjacency_list[18].push_back(Edge(24, 1));
	adjacency_list[18].push_back(Edge(12, 1));
	adjacency_list[19].push_back(Edge(14, 1));
	adjacency_list[19].push_back(Edge(26, 1));
	adjacency_list[19].push_back(Edge(25, 1));
	adjacency_list[19].push_back(Edge(13, 1));
	adjacency_list[20].push_back(Edge(15, 1));
	adjacency_list[20].push_back(Edge(27, 1));
	adjacency_list[20].push_back(Edge(26, 1));
	adjacency_list[20].push_back(Edge(14, 1));
	adjacency_list[21].push_back(Edge(0, 1));
	adjacency_list[21].push_back(Edge(28, 1));
	adjacency_list[21].push_back(Edge(27, 1));
	adjacency_list[21].push_back(Edge(15, 1));
	adjacency_list[22].push_back(Edge(16, 1));
	adjacency_list[22].push_back(Edge(0, 1));
	adjacency_list[22].push_back(Edge(0, 1));
	adjacency_list[22].push_back(Edge(0, 1));
	adjacency_list[23].push_back(Edge(17, 1));
	adjacency_list[23].push_back(Edge(0, 1));
	adjacency_list[23].push_back(Edge(0, 1));
	adjacency_list[23].push_back(Edge(16, 1));
	adjacency_list[24].push_back(Edge(18, 1));
	adjacency_list[24].push_back(Edge(0, 1));
	adjacency_list[24].push_back(Edge(0, 1));
	adjacency_list[24].push_back(Edge(17, 1));
	adjacency_list[25].push_back(Edge(19, 1));
	adjacency_list[25].push_back(Edge(0, 1));
	adjacency_list[25].push_back(Edge(0, 1));
	adjacency_list[25].push_back(Edge(18, 1));
	adjacency_list[26].push_back(Edge(20, 1));
	adjacency_list[26].push_back(Edge(0, 1));
	adjacency_list[26].push_back(Edge(0, 1));
	adjacency_list[26].push_back(Edge(19, 1));
	adjacency_list[27].push_back(Edge(21, 1));
	adjacency_list[27].push_back(Edge(0, 1));
	adjacency_list[27].push_back(Edge(0, 1));
	adjacency_list[27].push_back(Edge(20, 1));
	adjacency_list[28].push_back(Edge(0, 1));
	adjacency_list[28].push_back(Edge(0, 1));
	adjacency_list[28].push_back(Edge(0, 1));
	adjacency_list[28].push_back(Edge(21, 1));

	// Konsole öffnen
	open_console("my*QBert Debug Console");	
		
	// Coily Test
	Coily *c = new Coily(Node(1, &cubes[1]));
	npc_list.push_back(*c);
}

int spiel::step()
{
	unsigned char keys[256];
	DIMOUSESTATE mouse;

	qbert.Step(adjacency_list);

	for(std::list<NPC>::iterator it = npc_list.begin(); it != npc_list.end(); ++it)	
		it->Step(adjacency_list);

	if (poll_keyboard(keys))
	{
		// Q*Bert Steuerung
		if (keys[DIK_RIGHT])
			qbert.Move(DIR_RIGHTDOWN);
		else if (keys[DIK_LEFT])
			qbert.Move(DIR_LEFTUP);
		else if (keys[DIK_UP])
			qbert.Move(DIR_RIGHTUP);
		else if (keys[DIK_DOWN])
			qbert.Move(DIR_LEFTDOWN);

		// Zoom
		if (keys[DIK_ADD])
			cam_abstand -= 1.0f;
		else if (keys[DIK_SUBTRACT]) 
			cam_abstand += 1.0f;
	}

	// Blickrichtung
	if (poll_mouse(&mouse) && mouse.rgbButtons[0])
	{
		blickrichtung.x += mouse.lX / 100.0f;
		blickrichtung.y -= mouse.lY / 100.0f;
	}

	standort = cubes[8].lookatme(&blickrichtung, cam_abstand);

	return 0;
}

int spiel::render()
{
	step();

	for(int i=1;i<=28;i++)
		cubes[i].render(0, RENDER_OPAQUE);
	
	qbert.render(1, RENDER_ALL);
		
	for(std::list<NPC>::iterator it = npc_list.begin(); it != npc_list.end(); ++it)	
		it->render(1, RENDER_ALL);

	return 1;
}

spiel myQBert;