#include "Coily.h"

Coily::Coily(int coily_node)
{
	CurNode = coily_node;
	isUnpacked = false;
}

Coily::~Coily(void)
{
}

int Coily::Step(const AdjacencyList &adjacency_list, int qbert_node)
{	
	if (!isUnpacked)
	{		
		// Variablen
		int rnd = rand();
		int target;

		// Nach Rechts oder Unten (bzw. Links)?
		if (rnd%2)
			target = adjacency_list.adj[CurNode][1].target;
		else
			target = adjacency_list.adj[CurNode][2].target;

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
			CurNode = target;
		}
	}
	else if (CurNode != qbert_node)
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
	return CurNode;
}

int Coily::Step_Unpacked(const AdjacencyList &adjacency_list, int qbert_node)
{
	// Schlange einen Knoten in Richtung Q*Bert bewegen
	std::vector<double> min_distance;
	std::vector<int> previous;
	int n = adjacency_list.adj.size();
	int source = CurNode;
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
		const std::vector<Node> &neighbors = adjacency_list.adj[u];
		for (std::vector<Node>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end(); neighbor_iter++)
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

	std::list<int> path;
	for ( ; qbert_node != -1; qbert_node = previous[qbert_node])
		path.push_front(qbert_node);
	path.pop_front();

	/*
	std::list<int>::const_iterator iterator;
	for (iterator = path.begin(); iterator != path.end(); ++iterator)		
		 printf("%d ", *iterator);		
	*/

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