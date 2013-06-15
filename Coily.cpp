#include <fstream>
#include <limits>
#include <list>
#include <set>
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
	TexUnpacked.load("myQBert/Textures/Purple-Ball.png");
	TexUnpackedJump.load("myQBert/Textures/Purple-Ball-Jump.png");
}

Coily::~Coily(void)
{
}

int Coily::Step(const AdjacencyList &adjacency_list, Node QBertNode)
{
	// Wartet der NPC?
	if (isWaiting)
	{
		// Weiter warten..
		FramesWaited++;

		// Hat der NPC genug gewartet?
		if (FramesWaited == FramesPerWait)
		{
			// Freigeben
			FramesWaited = 0;
			isWaiting = false;
		}
	}
	else
	{
		// Bewegt sich der NPC?
		if (isMoving)
		{
			// Weiter bewegen..
			Move(MoveDirection);

			// Sind Coily und Q*Bert auf dem gleichen Knoten?
			if (CurNode.NodeNum == QBertNode.NodeNum)
			{
				// Coily hat Q*Bert gefangen
				Collision();
			}
		}
		else
		{
			// Ist der NPC nicht auf dem NULL Knoten?
			if (CurNode.NodeNum != 0)
			{
				// Ist Coily noch nicht entpackt?
				if (!isUnpacked)
				{
					// neuen Knoten und damit auch die neue Richtung zufällig bestimmen
					int rnd = rand() % 2;
					if (rnd%2)
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
						// Entpacken, nächsten Knoten berechnen und Richtung bestimmmen
						isUnpacked=true;
						TargetNode = Step_Unpacked(adjacency_list, QBertNode);
						if (adjacency_list[CurNode.NodeNum][0].target == TargetNode)
							MoveDirection = DIR_RIGHTUP;
						else if (adjacency_list[CurNode.NodeNum][1].target == TargetNode)
							MoveDirection = DIR_RIGHTDOWN;
						else if (adjacency_list[CurNode.NodeNum][2].target == TargetNode)
							MoveDirection = DIR_LEFTDOWN;
						else if (adjacency_list[CurNode.NodeNum][3].target == TargetNode)
							MoveDirection = DIR_LEFTUP;
					}

					// NPC bewegen
					isMoving = true;
					Move(MoveDirection);
				}
				// Sind Coily und Q*Bert nicht auf dem gleichen Knoten?
				else if (CurNode.NodeNum != QBertNode.NodeNum)
				{
					// nächsten Knoten berechnen und Richtung bestimmmen
					TargetNode = Step_Unpacked(adjacency_list, QBertNode);
					if (adjacency_list[CurNode.NodeNum][0].target == TargetNode)
						MoveDirection = DIR_RIGHTUP;
					else if (adjacency_list[CurNode.NodeNum][1].target == TargetNode)
						MoveDirection = DIR_RIGHTDOWN;
					else if (adjacency_list[CurNode.NodeNum][2].target == TargetNode)
						MoveDirection = DIR_LEFTDOWN;
					else if (adjacency_list[CurNode.NodeNum][3].target == TargetNode)
						MoveDirection = DIR_LEFTUP;

					// NPC bewegen
					isMoving = true;
					Move(MoveDirection);
				}
				else
				{
					// Coily hat Q*Bert gefangen
					Collision();
				}
			}
		}
	}

	return 0;
}

Node Coily::Step_Unpacked(const AdjacencyList &adjacency_list, Node qbert_node)
{
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
	for ( ; qbert_node.NodeNum != -1; qbert_node.NodeNum = previous[qbert_node.NodeNum])
		path.push_front(qbert_node);
	path.pop_front();
	return path.front();
}

int Coily::Collision(void)
{
	printf("%s", "GAME OVER, du Lusche!\n");
	return 0;
}

int Coily::NodeEffect(void)
{
	return 0;
}

int Coily::SetTexture(void)
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
	return 0;
}