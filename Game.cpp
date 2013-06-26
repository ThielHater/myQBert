#include <Windows.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Game.h"
#include "Edge.h"
#include "Node.h"
#include "Cube.h"
#include "Ball.h"
#include "RedBall.h"
#include "GreenBall.h"
#include "Coily.h"
#include "SlickSam.h"
#include "UggWrongWay.h"
#include "resource.h"

/*
	Zu erledigen:
	- noch ein paar Sounds
	- Disks
	- Fall der NPCs darstellen
*/

Game myqbert(31);

void Game::window_init(char *txt, WORD icon_num, int r, int g, int b)
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

void Game::window_mode(char *txt, bool full_screen)
{
	HWND handle = FindWindow(NULL, _TEXT(txt));
	if (full_screen)
	{
		SendMessage(handle, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		SetWindowLong(handle, GWL_STYLE, WS_POPUPWINDOW | WS_VISIBLE);
	}
	else
	{
		SetWindowLong(handle, GWL_STYLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE);
		SendMessage(handle, WM_SYSCOMMAND, SC_RESTORE, 0);
	}
}

void Game::load_cube_tex()
{
	std::stringstream ss;
	for (int i=0; i<3; i++)
	{
		ss <<"myQBert/Textures/Cube-L" <<stats.Level <<"-R" <<stats.Round <<"-" <<(i+1) <<".png";
		cube_tex[i].load((char*)ss.str().c_str());
		ss.str(std::string()); ss.clear();
	}
	return;
}

void Game::load_disk_tex()
{
	std::stringstream ss;
	for (int i=0; i<4; i++)
	{
		ss <<"myQBert/Textures/Disk-" <<(i+1) <<".png";
		disk_tex[i].load((char*)ss.str().c_str());
		ss.str(std::string()); ss.clear();
	}
	return;
}

void Game::setup()
{
	// Variablendeklaration
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	int rnd=0;
	int l=6;
	float dia=sqrt(50.0f);
	float x=l/2.0f*dia;
	float y=l*5.0f;
	float z=l*dia/2.0f;
	splashscreen intro;

	// Splashscreen darstellen
	intro.create("myQBert/Textures/Intro.bmp", 1, 1);

	// zuf�llige Zufallszahlen :)
	srand((long)time(NULL));

	// Titel, Icon und Hintergrundfarbe setzen
	window_init("myQ*Bert", IDI_MYICON, 0, 0, 0);
	intro.progress(10);

	// Frame Rate setzen
	frame_rate = 30;
	set_cps(frame_rate);

	// Knoten und Kanten aufbauen
	setup_nodes();

	// Sprites laden
	std::stringstream ss;
	for (int i=0; i<10; i++)
	{
		ss <<"myQBert/Textures/" <<i <<".png";
		digit_sprite[i].load((char*)ss.str().c_str(), 0xffffff00);
		ss.str(std::string()); ss.clear();
	}
	for (int i=0; i<3; i++)
	{
		ss <<"myQBert/Textures/Level-Splash-" <<(i+1) <<".png";
		splash_sprite[i].load((char*)ss.str().c_str(), 0xffffff00);
		ss.str(std::string()); ss.clear();
	}
	player_sprite.load("myQBert/Textures/Player.png", 0xffffff00);
	lvl_sprite.load("myQBert/Textures/Level.png", 0xffffff00);
	rnd_sprite.load("myQBert/Textures/Round.png", 0xffffff00);
	life_sprite.load("myQBert/Textures/Life.png", 0xffffff00);

	// Disk Texturen laden
	disk_tex[0].load("myQBert/Textures/Disk-1.png");
	disk_tex[1].load("myQBert/Textures/Disk-2.png");
	disk_tex[2].load("myQBert/Textures/Disk-3.png");
	disk_tex[3].load("myQBert/Textures/Disk-4.png");
	intro.progress(30);

	// W�rfel initialisieren
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
	intro.progress(40);

	// Scheiben initialisieren
	load_disk_tex();
	D3DXMatrixTranslation(&trans, -dia/2.0f, 5.0f, dia/2.0f);
	disks[0].load("Cube.x", "myQBert/Models");
	disks[0].init_texture(disk_tex);
	disks[0].disable_reflections();
	disks[0].add_transform(&trans);

	D3DXMatrixTranslation(&trans, 7.0f*dia -dia/2.0f, 5.0f, dia/2.0f);
	disks[1].load("Cube.x", "myQBert/Models");
	disks[1].init_texture(disk_tex);
	disks[1].disable_reflections();
	disks[1].add_transform(&trans);

	rnd = rand() % 6;
	D3DXMatrixTranslation(&trans, rnd*dia/2.0f, rnd*5.0f, rnd*dia/2.0f);
	disks[0].add_transform(&trans);
	if (rnd == 0)
	{
		adjacency_list[22][3].target.NodeNum=29;
		adjacency_list[22][3].target.RelCube=&disks[0];
	}
	else if (rnd == 1)
	{
		adjacency_list[16][3].target.NodeNum=29;
		adjacency_list[16][3].target.RelCube=&disks[0];
	}
	else if (rnd == 2)
	{
		adjacency_list[11][3].target.NodeNum=29;
		adjacency_list[11][3].target.RelCube=&disks[0];
	}
	else if (rnd == 3)
	{
		adjacency_list[7][3].target.NodeNum=29;
		adjacency_list[7][3].target.RelCube=&disks[0];
	}
	else if (rnd == 4)
	{
		adjacency_list[4][3].target.NodeNum=29;
		adjacency_list[4][3].target.RelCube=&disks[0];
	}
	else if (rnd == 5)
	{
		adjacency_list[2][3].target.NodeNum=29;
		adjacency_list[2][3].target.RelCube=&disks[0];
	}

	rnd = rand() % 6;
	D3DXMatrixTranslation(&trans, -(rnd*dia/2.0f), rnd*5.0f, rnd*dia/2.0f);
	disks[1].add_transform(&trans);
	if (rnd == 0)
	{
		adjacency_list[28][0].target.NodeNum=30;
		adjacency_list[28][0].target.RelCube=&disks[1];
	}
	else if (rnd == 1)
	{
		adjacency_list[21][0].target.NodeNum=30;
		adjacency_list[21][0].target.RelCube=&disks[1];
	}
	else if (rnd == 2)
	{
		adjacency_list[15][0].target.NodeNum=30;
		adjacency_list[15][0].target.RelCube=&disks[1];
	}
	else if (rnd == 3)
	{
		adjacency_list[10][0].target.NodeNum=30;
		adjacency_list[10][0].target.RelCube=&disks[1];
	}
	else if (rnd == 4)
	{
		adjacency_list[6][0].target.NodeNum=30;
		adjacency_list[6][0].target.RelCube=&disks[1];
	}
	else if (rnd == 5)
	{
		adjacency_list[3][0].target.NodeNum=30;
		adjacency_list[3][0].target.RelCube=&disks[1];
	}
	intro.progress(60);

	/* Sounds laden
		0. Coily-Fall
		1. Coily-Hit
		2. Coily-Jump
		3. Disk
		4. End-Round
		5. Extra-Life
		6. Green-Ball
		7. Intro
		8. Level-1
		9. Level-2
		10. Level-3
		11. Other-Hit
		12. Other-Jump
		13. QBert-Drop
		14. QBert-Fall
		15. QBert-Hello
		16. QBert-Jump
		17. QBert-Swear-1
		18. QBert-Swear-2
		19. QBert-Swear-3
		20. Red-Ball
		21. SlickSam-Hit
	*/
	load_sounds(22, "myQBert/Sounds/Coily-Fall.wav", "myQBert/Sounds/Coily-Hit.wav", "myQBert/Sounds/Coily-Jump.wav", "myQBert/Sounds/Disk.wav", "myQBert/Sounds/End-Round.wav", "myQBert/Sounds/Extra-Life.wav", "myQBert/Sounds/Green-Ball.wav", "myQBert/Sounds/Intro.wav", "myQBert/Sounds/Level-1.wav", "myQBert/Sounds/Level-2.wav", "myQBert/Sounds/Level-3.wav", "myQBert/Sounds/Other-Hit.wav", "myQBert/Sounds/Other-Jump.wav", "myQBert/Sounds/QBert-Drop.wav", "myQBert/Sounds/QBert-Fall.wav", "myQBert/Sounds/QBert-Hello.wav", "myQBert/Sounds/QBert-Jump.wav", "myQBert/Sounds/QBert-Swear-1.wav", "myQBert/Sounds/QBert-Swear-2.wav", "myQBert/Sounds/QBert-Swear-3.wav", "myQBert/Sounds/Red-Ball.wav", "myQBert/Sounds/SlickSam-Hit.wav");
	intro.progress(70);

	// Kamera
	set_perspektive(D3DX_PI/4.0f, 1.0f, 1000.0f);
	blickrichtung = D3DXVECTOR3(0, -D3DX_PI/6.0f, 1.0f);
	standort = cubes[8].lookatme(&blickrichtung, 15.0f);
	set_sunlight(0, &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 0.0f);

	// Q*Bert spawnen
	qbert = new QBert(Node(1, &cubes[1]));

	/*
	// Konsole �ffnen
	open_console("myQ*Bert Debug Console");
	*/

	// Splashscreen ausblenden
	//Sleep(2000);
	intro.progress(100);
	//Sleep(2000);
	intro.release();

	// Vollbild
	window_mode("myQ*Bert", true);

	// Sound abspielen
	myqbert.play_sound(8, 0);
}

void Game::setup_nodes()
{
	// Abgrund
	adjacency_list[0].push_back(Edge(Node(0, &cubes[0]), 1));

	// W�rfel
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

	// Scheiben
	adjacency_list[29].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[29].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[29].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[29].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[30].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[30].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[30].push_back(Edge(Node(1, &cubes[1]), 1));
	adjacency_list[30].push_back(Edge(Node(1, &cubes[1]), 1));
}

bool Game::check_round()
{
	if ((stats.Level == 1) || (stats.Level == 2))
	{
		for (int i=1; i<=28; i++)
			if (cubes[i].cur != stats.Level)
				return false;
	}
	else if (stats.Level == 3)
	{
		for (int i=1; i<=28; i++)
			if (cubes[i].cur != 1)
				return false;
	}
	return true;
}

void Game::new_round()
{
	qbert->CurNode = Node(1, &cubes[1]);
	qbert_hit();

	if (stats.Round != 4)
	{
		stats.Round++;
	}
	else
	{
		stats.ShowSplash = true;
		stats.Round = 1;
		stats.Level++;
		if (stats.Level == 2)
			myqbert.play_sound(9, 0);
		else if (stats.Level == 3)
			myqbert.play_sound(10, 0);
	}

	load_cube_tex();

	for (int i=1; i<=28; i++)
		cubes[i].init_texture(cube_tex);
}

void Game::qbert_hit()
{
	D3DXMATRIX pos;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	D3DXMATRIX null;
	qbert->isMoving = false;
	qbert->isWaiting = true;
	qbert->FirstMoveDone = false;
	qbert->FramesJumped = 0;
	qbert->FramesWaited = 0;
	qbert->TargetNode.NodeNum = 0;
	qbert->TargetNode.RelCube = 0;
	qbert->CurNode.RelCube->get_transform(&pos);
	D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
	D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
	D3DXMatrixTranslation(&null, 0, 0,0);
	if (stats.QBertHit)
	{
		qbert->load("TriPrismH.x", "myQBert/Models");
		if (qbert->MoveDirection == DIR_RIGHTUP)
			qbert->set_texture(0, &qbert->TexUpRightBalloon);
		else if (qbert->MoveDirection == DIR_RIGHTDOWN)
			qbert->set_texture(0, &qbert->TexDownRightBalloon);
		else if ((qbert->MoveDirection == DIR_LEFTDOWN) || (qbert->MoveDirection == DIR_NONE))
			qbert->set_texture(0, &qbert->TexDownLeftBalloon);
		else if (qbert->MoveDirection == DIR_LEFTUP)
			qbert->set_texture(0, &qbert->TexUpLeftBalloon);
		int rnd = 1 + rand() % 3;
		if (rnd == 1)
			myqbert.play_sound(17, 0);
		else if (rnd == 2)
			myqbert.play_sound(18, 0);
		else if (rnd == 3)
			myqbert.play_sound(19, 0);
	}
	else
	{
		qbert->load("TriPrism.x", "myQBert/Models");
		if (qbert->MoveDirection == DIR_RIGHTUP)
			qbert->set_texture(0, &qbert->TexUpRight);
		else if (qbert->MoveDirection == DIR_RIGHTDOWN)
			qbert->set_texture(0, &qbert->TexDownRight);
		else if ((qbert->MoveDirection == DIR_LEFTDOWN) || (qbert->MoveDirection == DIR_NONE))
			qbert->set_texture(0, &qbert->TexDownLeft);
		else if (qbert->MoveDirection == DIR_LEFTUP)
			qbert->set_texture(0, &qbert->TexUpLeft);
		qbert->MoveDirection = DIR_NONE;
		stats.FramesLastSpawn = 0;

		for(std::vector<NPC*>::iterator it = npc_list.begin(); it != npc_list.end(); ++it)
			delete *it;

		npc_list.clear();
	}
	qbert->set_transform(&null);
	qbert->add_transform(&rota);
	qbert->add_transform(&pos);
	qbert->add_transform(&trans);
}

void Game::reset()
{
	qbert->CurNode = Node(1, &cubes[1]);
	qbert_hit();

	stats.Reset();

	load_cube_tex();

	for (int i=1; i<=28; i++)
		cubes[i].init_texture(cube_tex);

	myqbert.play_sound(8, 0);
}

void Game::game_over()
{
	/* Frage: Was sollen wir machen? */

	printf("Game Over, du Lusche!\n\n");
	reset();
}

void Game::step()
{
	// Wurde Q*Bert nicht getroffen, ist die Runde nicht zu Ende, soll der Splashscreen nicht dargestellt werden und ist das Spiel nicht pausiert?
	if (!stats.QBertHit && !stats.RoundDone && !stats.ShowSplash && !stats.Pause)
	{
		// Ist Q*Bert nicht auf einer Disk?
		if (!stats.QBertOnDisk)
		{
			// Array f�r Tastatureingaben
			unsigned char keys[256];

			// Wurde eine Taste gedr�ckt?
			if (poll_keyboard(keys))
			{
				// Q*Bert ziehen
				if (keys[DIK_RIGHT])
					qbert->Step(myqbert, adjacency_list, stats, DIR_RIGHTDOWN);
				else if (keys[DIK_LEFT])
					qbert->Step(myqbert, adjacency_list, stats, DIR_LEFTUP);
				else if (keys[DIK_UP])
					qbert->Step(myqbert, adjacency_list, stats, DIR_RIGHTUP);
				else if (keys[DIK_DOWN])
					qbert->Step(myqbert, adjacency_list, stats, DIR_LEFTDOWN);
				else
					qbert->Step(myqbert, adjacency_list, stats, DIR_NONE);

				// Ist Q*Bert runtergefallen?
				if (qbert->CurNode.NodeNum == 0)
				{
					game_over();
					return;
				}

				// Ist Q*Bert auf einen W�rfel geh�pft?
				else if (!qbert->isMoving && ((qbert->CurNode.NodeNum == 29) || (qbert->CurNode.NodeNum == 30)))
				{
					if (qbert->CurNode.NodeNum == 29)
					{
						qbert->set_texture(0, &qbert->TexDownRight);
						disks[0].isUsed = true;
					}
					else
					{
						qbert->set_texture(0, &qbert->TexDownLeft);
						disks[1].isUsed = true;
					}
					stats.QBertOnDisk=true;
					return;
				}
			}
		}
		else
		{
			// War Q*Bert 3 Sekunden auf der Disk?
			if (stats.FramesQBertOnDisk == frame_rate*3)
			{
				// Variablendeklaration
				D3DXMATRIX pos;
				D3DXMATRIX rota;
				D3DXMATRIX trans;
				D3DXMATRIX null;

				// Q*Bert absetzen
				stats.QBertOnDisk = false;
				stats.FramesQBertOnDisk = 0;
				qbert->CurNode = Node(1, &cubes[1]);
				qbert->isMoving = false;
				qbert->isWaiting = true;
				qbert->FirstMoveDone = false;
				qbert->FramesJumped = 0;
				qbert->FramesWaited = 0;
				qbert->TargetNode.NodeNum = 0;
				qbert->TargetNode.RelCube = 0;
				qbert->CurNode.RelCube->get_transform(&pos);
				D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
				D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
				D3DXMatrixTranslation(&null, 0, 0,0);
				qbert->MoveDirection = DIR_NONE;
				qbert->set_transform(&null);
				qbert->add_transform(&rota);
				qbert->add_transform(&pos);
				qbert->add_transform(&trans);

				// W�rfel umf�rben
				qbert->NodeEffect(stats);
			}
			else
			{
				stats.FramesQBertOnDisk++;
			}
		}

		// alle X Sekunden neuen NPC spawnen
		if (stats.FramesLastSpawn >= (frame_rate*10 - frame_rate*2*stats.Level))
		{
			// NPC ausw�rfeln und einketten
			int rnd = 1 + (rand() % 4);
			int i = 2 + (rand() % 2);
			if (rnd == 1)
			{
				Ball *b;
				if (npc_list.empty())
					b = new RedBall(Node(i, &cubes[i]));
				else
					b = new GreenBall(Node(i, &cubes[i]));
				npc_list.push_back(b);
			}
			else if (rnd == 2)
			{
				Coily *c = new Coily(Node(i, &cubes[i]));
				npc_list.push_back(c);
			}
			else if (rnd == 3)
			{
				SlickSam *ss = new SlickSam(Node(i, &cubes[i]));
				npc_list.push_back(ss);
			}
			else if (rnd == 4)
			{
				i = (i == 2) ? 22 : 28;
				UggWrongWay *uww = new UggWrongWay(Node(i, &cubes[i]));
				npc_list.push_back(uww);
			}

			// Spawn Timer zur�cksetzen
			stats.FramesLastSpawn = 0;
		}

		// Steht die Zeit nicht still?
		if (!stats.TimeFrozen)
		{
			// Scheiben drehen
			if (stats.FramesLastSpawn % 3 == 0)
			{
				disks[0].update_texture();
				disks[1].update_texture();
			}

			// NPCs durchlaufen
			std::vector<NPC*>::iterator it = npc_list.begin();
			while (it != npc_list.end())
			{
				// NPC ziehen
				(*it)->Step(myqbert, adjacency_list, stats, qbert->CurNode, qbert->TargetNode);

				// Game Over?
				if (stats.LifeCount == 0)
				{
					stats.QBertHit = false; // kleiner Hack :)
					game_over();
					return;
				}

				// Wurde Q*Bert getroffen?
				else if (stats.QBertHit)
				{
					qbert_hit();
					return;
				}

				// Ist der NPC runtergefallen oder die Zeit angehalten worden?
				else if (((*it)->CurNode.NodeNum == 0) || (stats.TimeFrozen))
				{
					// NPC entfernen
					delete *it;
					it = npc_list.erase(it);
					continue;
				}

				// n�chster NPC
				++it;
			}

			// Wurde die Runde abgeschlossen?
			if (check_round())
			{
				stats.RoundDone = true;
				myqbert.play_sound(4, 0);
			}

			// Spawn Timer hochz�hlen
			stats.FramesLastSpawn++;
		}
		else
		{
			// War die Zeit 3 Sekunden gefroren?
			if (stats.FramesTimeFrozen == frame_rate*3)
			{
				// Zeit auftauen
				stats.TimeFrozen = false;
				stats.FramesTimeFrozen = 0;
				set_bkcolor(0, 0, 0);
			}
			else
			{
				// Epileptiker-Warnung??
				int rnd = 1 + rand() % 4;
				if (rnd == 1)
					set_bkcolor(155, 121, 60);
				else if (rnd == 2)
					set_bkcolor(161, 98, 229);
				else if (rnd == 3)
					set_bkcolor(165, 60, 117);
				else if (rnd == 4)
					set_bkcolor(155, 65, 38);
				stats.FramesTimeFrozen++;
			}
		}
	}
	else
	{
		// Wurde Q*Bert getroffen?
		if (stats.QBertHit)
		{
			// War die Zeit 2 Sekunden angehalten?
			if (stats.FramesQBertHit == frame_rate*2)
			{
				// Q*Bert freigeben
				stats.QBertHit = false;
				stats.FramesQBertHit = 0;
				qbert_hit();
			}
			else
			{
				stats.FramesQBertHit++;
			}
		}

		// Ist die Runde zu Ende?
		else if (stats.RoundDone)
		{
			// War die Zeit 3 Sekunden angehalten?
			if (stats.FramesRoundDone == frame_rate*3)
			{
				// Spiel freigeben
				stats.RoundDone = false;
				stats.FramesRoundDone = 0;
				set_bkcolor(0, 0, 0);
				new_round();
			}
			else
			{
				// Epileptiker-Warnung??
				int rnd = rand() % 3;
				for (int i=1; i<=28; i++)
				{
					cubes[i].cur = rnd;
					cubes[i].update_texture();
				}
				stats.FramesRoundDone++;
			}
		}

		// Soll der Splashscreen dargestellt werden?
		else if (stats.ShowSplash)
		{
			// Wurde der Splashscreen 3 Sekunden dargestellt?
			if (stats.FramesSplashShown == frame_rate*3)
			{
				stats.ShowSplash = false;
				stats.FramesSplashShown = 0;
			}
			else
			{
				stats.FramesSplashShown++;
			}
		}
	}
	stats.FramesPauseChanged++;
}

void Game::render_sprites()
{
	// Ist die Runde nicht zu Ende?
	if (!stats.ShowSplash)
	{
		// Variablendeklaration und -initialisierung
		int digit = 0;
		int digit_count = (stats.Score > 0) ? 0 : 1;
		int score = stats.Score;
		int edge = 32;
		int x = 0; int y = 0;

		// Fenstergr��e abfragen und Rastereinheit ausrechnen
		get_windowsize(0, 0, &x, &y, 1);
		x = x/32; y = y/32;

		// Player rendern
		player_sprite.move(x, y*2, x + player_sprite.get_x(), y*2 + player_sprite.get_y());
		player_sprite.render();

		// Anzahl der Stellen ermitteln
		while (score)
		{
			score = score / 10;
			digit_count++;
		}

		// alle Stellen durchlaufen und Ziffer rendern
		score = stats.Score;
		for (int i=digit_count-1; i>=0; i--)
		{
			digit = score % 10;
			score = score / 10;
			digit_sprite[digit].move(x + i*(digit_sprite[digit].get_x()/2), y*5, x + (i+1)*(digit_sprite[digit].get_x()/2), y*5 + (digit_sprite[digit].get_y())/2);
			digit_sprite[digit].render();
		}

		// Level / Round rendern
		lvl_sprite.move(x*24, y*6, x*24 + lvl_sprite.get_x()/2, y*6 + lvl_sprite.get_y()/2);
		lvl_sprite.render();
		rnd_sprite.move(x*24, y*9, x*24 + rnd_sprite.get_x()/2, y*9 + rnd_sprite.get_y()/2);
		rnd_sprite.render();
		digit_sprite[stats.Level].move(x*24 + lvl_sprite.get_x()/2 + digit_sprite[stats.Level].get_x()/2, y*6, x*24 + lvl_sprite.get_x()/2 + digit_sprite[stats.Level].get_x(), y*6 + digit_sprite[stats.Level].get_y()/2);
		digit_sprite[stats.Level].render();
		digit_sprite[stats.Round].move(x*24 + rnd_sprite.get_x()/2 + digit_sprite[stats.Level].get_x()/2, y*9, x*24 + rnd_sprite.get_x()/2 + digit_sprite[stats.Round].get_x(), y*9 + digit_sprite[stats.Round].get_y()/2);
		digit_sprite[stats.Round].render();

		// Leben rendern
		for (int i=0; i<stats.LifeCount; i++)
		{
			life_sprite.move(x, y*12 + i*(life_sprite.get_y()/2), x + (life_sprite.get_x()/2), y*12 + (i+1)*(life_sprite.get_y()/2));
			life_sprite.render();
		}
	}
	else
	{
		// Variablendeklaration und -initialisierung
		int x = 0; int y = 0;

		// Splashscreen darstellen
		get_windowsize(0, 0, &x, &y, 1);
		splash_sprite[stats.Level-1].move(0, 0, x, y);
		splash_sprite[stats.Level-1].render();
	}
}

int Game::render()
{
	// Sicherheitsabfrage
	if (stats.Level != 4)
	{
		// Array f�r Tastatureingaben
		unsigned char keys[256];

		// Elemente auf dem Spielfeld berechnen
		step();

		// W�rfel und Scheiben rendern
		for(int i=1;i<=28;i++)
			cubes[i].render(0, RENDER_OPAQUE);
		disks[0].render(1, RENDER_ALL);
		disks[1].render(1, RENDER_ALL);

		// Q*Bert rendern
		qbert->render(1, RENDER_ALL);

		// NPCs rendern
		for(std::vector<NPC*>::iterator it = npc_list.begin(); it != npc_list.end(); ++it)
			(*it)->render(1, RENDER_ALL);

		// Sprites rendern
		render_sprites();

		// Wurde eine Taste gedr�ckt?
		if (poll_keyboard(keys))
		{
			if (keys[DIK_F1])
			{
				// Screenshot machen
				screenshot("myQBert");
			}
			else if ((keys[DIK_F2] || keys[DIK_PAUSE] || keys[DIK_P]) && (stats.FramesPauseChanged >= 10))
			{
				// Spiel pausieren
				stats.FramesPauseChanged = 0;
				stats.Pause = !stats.Pause;
			}
			else if (keys[DIK_F3])
			{
				// Fenstermodus
				window_mode("myQ*Bert", false);
			}
			else if (keys[DIK_F4])
			{
				// Vollbildmodus
				window_mode("myQ*Bert", true);
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}
}