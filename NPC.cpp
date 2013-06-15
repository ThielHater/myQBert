#include "NPC.h"
#include <sstream>
#include <string>

NPC::NPC(void)
{
	isMoving = false;
	MoveDirection = DIR_NONE;
	FramesPerJump = 10;
	CurNode.NodeNum = 0;
	CurNode.RelCube = 0;
}

NPC::NPC(Node ArgCurNode)
{
	isMoving = false;
	MoveDirection = DIR_NONE;
	FramesPerJump = 0;
	CurNode=ArgCurNode;
}

void NPC::InitGraphics(char *ArgTexName)
{
	D3DXMATRIX pos;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	CurNode.RelCube->get_transform(&pos);
	D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
	D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
	isMoving = false;
	load("TriPrism.x", "myQBert/Models");	
	std::stringstream ss;
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Down-Left.png";
	TexDownLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Down-Left-Jump.png";
	TexDownLeftJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Down-Right.png";
	TexDownRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Down-Right-Jump.png";
	TexDownRightJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Up-Left.png";
	TexUpLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Up-Left-Jump.png";
	TexUpLeftJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Up-Right.png";
	TexUpRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<ArgTexName <<"-Up-Right-Jump.png";
	TexUpRightJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	set_texture(0, &TexDownLeft);
	disable_reflections();
	add_transform(&rota);
	add_transform(&pos);
	add_transform(&trans);
}

NPC::~NPC(void)
{
}

void NPC::Move(DirectionEnum direction)
{
	if (!isMoving)
	{
		isMoving = true;
		MoveDirection = direction;
	}
}

int NPC::Step(const AdjacencyList &adjacency_list)
{
	if (!isMoving)	
		return 0;	

	enum first_move_e { MOVE_Y, MOVE_XZ };

	// Wenn wir nach unten springen, erst über die XZ Achse bewegen, sonst erst über die Y Achse
	first_move_e first_move = (MoveDirection == DIR_LEFTDOWN || MoveDirection == DIR_RIGHTDOWN) ? MOVE_XZ : MOVE_Y;

	static int moved_sum = 0;
	static bool first_move_done = false;

	D3DXMATRIX tr;
	float sx = sqrt(50.0f) / 2 / FramesPerJump; // halbe Diagonale
	float sz = sx;
	float sy = 5.0f / FramesPerJump; // Seitenlänge
		
	// über Y-Achse bewegen
	if (first_move == MOVE_Y && !first_move_done || first_move == MOVE_XZ && first_move_done) {
		if (MoveDirection == DIR_LEFTDOWN || MoveDirection == DIR_RIGHTDOWN)
			D3DXMatrixTranslation(&tr, 0, -sy, 0);
		else
			D3DXMatrixTranslation(&tr, 0, sy, 0);
	}
	// über XZ-Achse bewegen
	else {
		if (MoveDirection == DIR_LEFTDOWN)
			D3DXMatrixTranslation(&tr, -sx, 0, -sz);
		else if (MoveDirection == DIR_LEFTUP)
			D3DXMatrixTranslation(&tr, -sx, 0, sz);
		else if (MoveDirection == DIR_RIGHTDOWN)
			D3DXMatrixTranslation(&tr, sx, 0, -sz);
		else if (MoveDirection == DIR_RIGHTUP)
			D3DXMatrixTranslation(&tr, sx, 0, sz);
	}

	// Bewegung fertig?
	if (moved_sum >= FramesPerJump) {
		if (first_move_done) {
			isMoving = false;
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