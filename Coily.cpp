#include "Coily.h"
#include <vector>
#include <string>
#include <list>
#include <limits> 
#include <set>
#include <utility> 
#include <algorithm>
#include <iterator>
#include <time.h>

Coily::Coily(Node ArgCurNode) : NPC(ArgCurNode)
{
	FramesPerJump = 5;
	isUnpacked = false;
	InitGraphics("Coily");
}

Coily::~Coily(void)
{
}

int Coily::Step(const AdjacencyList &adjacency_list, Node qbert_node)
{	
	if (!isUnpacked)
	{		
		// Variablen
		int rnd = rand();
		int target;

		// Nach Rechts oder Links (bzw. Unten)?
		if (rnd%2)
			target = adjacency_list[CurNode.NodeNum][1].target;
		else
			target = adjacency_list[CurNode.NodeNum][2].target;

		// Wurde die untere Kante erreicht (Coily kann am Anfang nicht seitlich runterfallen)?
		if (target == 0)
		{
			// Entpacken und nächsten Knoten ermitteln
			isUnpacked=true;
			CurNode = Step_Unpacked(adjacency_list, qbert_node);
		}
		else
		{
			// Zielknoten setzen
			CurNode.NodeNum = target;
		}
	}
	else if (CurNode.NodeNum != qbert_node.NodeNum)
	{
		// nächsten Knoten ermitteln
		CurNode = Step_Unpacked(adjacency_list, qbert_node);
	}
	else
	{
		// Coily hat Q*Bert gefangen
		Collision();
	}

	// Knoten zurückgeben
	return CurNode.NodeNum;
}

Node Coily::Step_Unpacked(const AdjacencyList &adjacency_list, Node qbert_node)
{
	// Schlange einen Knoten in Richtung Q*Bert bewegen
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
			int v = neighbor_iter->target;
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

	// nächsten Knoten zurückgeben
	return path.front();	
}

int Coily::Collision(void)
{
	return 0;
}

int Coily::NodeEffect(void)
{
	return 0;
}