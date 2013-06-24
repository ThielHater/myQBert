#include <fstream>
#include <limits>
#include <list>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "Coily.h"
#include "Node.h"

Coily::Coily(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	FramesPerWait = 5;
	isUnpacked = false;
	InitGraphics("Coily");
}

Coily::~Coily(void)
{
}

void Coily::InitGraphics(char *TexName)
{
	D3DXMATRIX pos;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	CurNode.RelCube->get_transform(&pos);
	D3DXMatrixRotationY(&rota, -D3DX_PI/2.0f);
	D3DXMatrixTranslation(&trans, 0, 5.0f, 0);
	if (isUnpacked)
		load("TriPrismH.x", "myQBert/Models");
	else
		load("TriPrism.x", "myQBert/Models");
	std::stringstream ss;
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Left.png";
	TexDownLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Left-Jump.png";
	TexDownLeftJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Right.png";
	TexDownRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Down-Right-Jump.png";
	TexDownRightJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Left.png";
	TexUpLeft.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Left-Jump.png";
	TexUpLeftJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Right.png";
	TexUpRight.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	ss <<"myQBert/Textures/" <<TexName <<"-Up-Right-Jump.png";
	TexUpRightJump.load((char*)ss.str().c_str());
	ss.str(std::string()); ss.clear();
	TexUnpacked.load("myQBert/Textures/Purple-Ball.png");
	TexUnpackedJump.load("myQBert/Textures/Purple-Ball-Jump.png");
	set_texture(0, &TexDownLeft);
	disable_reflections();
	add_transform(&rota);
	add_transform(&pos);
	add_transform(&trans);
	return;
}

void Coily::Step(const AdjacencyList &adjacency_list, GameStats &stats, const Node qbert_cur_node, const Node qbert_tar_node)
{
	// Wartet Coily?
	if (isWaiting)
	{
		// Weiter warten..
		FramesWaited++;

		// Hat Coily genug gewartet?
		if (FramesWaited == FramesPerWait)
		{
			// Freigeben
			FramesWaited = 0;
			isWaiting = false;
		}
	}
	else
	{
		// Bewegt sich Coily?
		if (isMoving)
		{
			// Weiter bewegen..
			Move(MoveDirection);			

			// Springen Coily und Q*Bert sich entgegen?
			if ((CurNode.NodeNum == qbert_tar_node.NodeNum) && (TargetNode.NodeNum == qbert_cur_node.NodeNum))
				Collision(stats);

			// Bewegung fertig?
			if (!isMoving)
			{
				// Sind Coily und Q*Bert auf dem gleichen Knoten?
				if (CurNode.NodeNum == qbert_cur_node.NodeNum)
					Collision(stats);
			}
		}
		else
		{
			// Ist Coily noch nicht entpackt?
			if (!isUnpacked)
			{
				// neuen Knoten und damit auch die neue Richtung zufällig bestimmen
				int rnd = rand() % 2;
				if (rnd)
				{
					TargetNode = adjacency_list[CurNode.NodeNum][1].target;
					MoveDirection = DIR_RIGHTDOWN;
				}
				else
				{
					TargetNode = adjacency_list[CurNode.NodeNum][2].target;
					MoveDirection = DIR_LEFTDOWN;
				}

				// Wurde die untere Kante erreicht (Coily kann am Anfang nicht seitlich runterfallen)?
				if (TargetNode.NodeNum == 0)
				{
					// Coily entpacken und anderes Modell laden
					isUnpacked=true;
					InitGraphics("Coily");

					// Sind Coily und Q*Bert gerade jetzt auf dem gleichen Knoten (Sonderfall)?
					if (CurNode.NodeNum == qbert_cur_node.NodeNum)
					{
						// Coily hat Q*Bert "gefangen"
						Collision(stats);
						return;
					}

					// nächsten Knoten berechnen und Richtung bestimmmen
					TargetNode = Step_Unpacked(adjacency_list, qbert_cur_node);
					if (adjacency_list[CurNode.NodeNum][0].target == TargetNode)
						MoveDirection = DIR_RIGHTUP;
					else if (adjacency_list[CurNode.NodeNum][1].target == TargetNode)
						MoveDirection = DIR_RIGHTDOWN;
					else if (adjacency_list[CurNode.NodeNum][2].target == TargetNode)
						MoveDirection = DIR_LEFTDOWN;
					else if (adjacency_list[CurNode.NodeNum][3].target == TargetNode)
						MoveDirection = DIR_LEFTUP;
				}

				// Coily bewegen
				isMoving = true;
				Move(MoveDirection);
			}

			// Sind Coily und Q*Bert nicht auf dem gleichen Knoten?
			else if (CurNode.NodeNum != qbert_cur_node.NodeNum)
			{
				// nächsten Knoten berechnen und Richtung bestimmmen
				TargetNode = Step_Unpacked(adjacency_list, qbert_cur_node);
				if (adjacency_list[CurNode.NodeNum][0].target == TargetNode)
					MoveDirection = DIR_RIGHTUP;
				else if (adjacency_list[CurNode.NodeNum][1].target == TargetNode)
					MoveDirection = DIR_RIGHTDOWN;
				else if (adjacency_list[CurNode.NodeNum][2].target == TargetNode)
					MoveDirection = DIR_LEFTDOWN;
				else if (adjacency_list[CurNode.NodeNum][3].target == TargetNode)
					MoveDirection = DIR_LEFTUP;

				// Coily bewegen
				isMoving = true;
				Move(MoveDirection);
			}
			else
			{
				// Coily hat Q*Bert gefangen
				Collision(stats);
			}
		}
	}
	return;
}

Node Coily::Step_Unpacked(const AdjacencyList &adjacency_list, Node qbert_cur_node)
{
	/* Djikstra-Algorithmus */

	std::vector<double> min_distance;
	std::vector<int> previous;
	int n = adjacency_list.size();
	int source = CurNode.NodeNum;
	double max_weight = std::numeric_limits<double>::infinity();

	min_distance.clear();
	min_distance.resize(n, max_weight);
	min_distance[source] = 0;
	previous.clear();
	previous.resize(n, -1);
	std::set<std::pair<double, int> > vertex_queue;
	vertex_queue.insert(std::make_pair(min_distance[source], source));

	while (!vertex_queue.empty())
	{
		double dist = vertex_queue.begin()->first;
		int u = vertex_queue.begin()->second;
		vertex_queue.erase(vertex_queue.begin());
		const std::vector<Edge> &neighbors = adjacency_list[u];
		for (std::vector<Edge>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end(); neighbor_iter++)
		{
			int v = neighbor_iter->target.NodeNum;
			double weight = neighbor_iter->weight;
			double distance_through_u = dist + weight;
			if (distance_through_u < min_distance[v])
			{
				vertex_queue.erase(std::make_pair(min_distance[v], v));
				min_distance[v] = distance_through_u;
				previous[v] = u;
				vertex_queue.insert(std::make_pair(min_distance[v], v));
			}
		}
	}

	std::list<Node> path;
	for ( ; qbert_cur_node.NodeNum != -1; qbert_cur_node.NodeNum = previous[qbert_cur_node.NodeNum])
		path.push_front(qbert_cur_node);
	path.pop_front();
	return path.front();
}

void Coily::Collision(GameStats &stats)
{
	stats.LifeCount--;
	stats.QBertHit = true;
	if (stats.LifeCount > 0)
		printf("Q*Bert wurde von Coily gefangen, noch %d Leben!\n", stats.LifeCount);
	else
		printf("Q*Bert wurde von Coily gefangen, kein Leben mehr!\n", stats.LifeCount);
	return;
}

void Coily::NodeEffect(GameStats &stats)
{
	return;
}

void Coily::SetTexture(void)
{
	if (isUnpacked)
	{
		if (isMoving)
		{
			if (MoveDirection == DIR_LEFTDOWN)
				set_texture(0, &this->TexDownLeftJump);
			else if (MoveDirection == DIR_RIGHTDOWN)
				set_texture(0, &this->TexDownRightJump);
			else if (MoveDirection == DIR_LEFTUP)
				set_texture(0, &this->TexUpLeftJump);
			else if (MoveDirection == DIR_RIGHTUP)
				set_texture(0, &this->TexUpRightJump);
		}
		else
		{
			if (MoveDirection == DIR_LEFTDOWN)
				set_texture(0, &this->TexDownLeft);
			else if (MoveDirection == DIR_RIGHTDOWN)
				set_texture(0, &this->TexDownRight);
			else if (MoveDirection == DIR_LEFTUP)
				set_texture(0, &this->TexUpLeft);
			else if (MoveDirection == DIR_RIGHTUP)
				set_texture(0, &this->TexUpRight);
		}
	}
	else
	{
		if (isMoving)
			set_texture(0, &this->TexUnpackedJump);
		else
			set_texture(0, &this->TexUnpacked);
	}
	return ;
}