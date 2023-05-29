/*
Name: Shubham Panchal
Roll no: 21356 - G3
 You have a business with several offices; you want to lease phone lines to connect 
them up with each other; and the phone company charges different amounts of 
money to connect different pairs of cities. You want a set of lines that connects all 
your offices with a minimum total cost. Solve the problem by suggesting 
appropriate data structures.
*/

#include <iostream>
#include <vector>
#include "linkedqueue.cpp"
#include <algorithm>
using namespace std;

struct Node
{
	char name;
	int weight = 0;
	Node *next = nullptr;
	Node *down = nullptr;
};

struct Edge
{
	char v1;
	char v2;
	int weight;
};

class Graph
{

	Node *HEAD = nullptr;
	vector<Edge> edges;
	int numVertices = 0;

	void add(char nodeA, char nodeB, int weight)
	{
		if (HEAD == nullptr)
		{
			Node *A = new Node();
			Node *B = new Node();
			A->name = nodeA;
			B->name = nodeB;
			B->weight = weight;
			A->next = B;
			HEAD = A;
			numVertices++;
		}
		else
		{
			Node *currentNode = HEAD;
			bool found = false;
			Node *prevNode = nullptr;
			while (currentNode != nullptr)
			{
				if (currentNode->name == nodeA)
				{
					Node *neighbor = currentNode->next;
					while (neighbor->next != nullptr)
					{
						neighbor = neighbor->next;
					}
					Node *B = new Node();
					B->name = nodeB;
					B->weight = weight;
					neighbor->next = B;
					found = true;
					break;
				}
				prevNode = currentNode;
				currentNode = currentNode->down;
			}
			if (!found)
			{
				Node *A = new Node();
				Node *B = new Node();
				A->name = nodeA;
				B->name = nodeB;
				B->weight = weight;
				A->next = B;
				prevNode->down = A;
				numVertices++;
			}
		}
	}

public:
	void addEdge(char nodeA, char nodeB, int weight)
	{
		add(nodeA, nodeB, weight);
		add(nodeB, nodeA, weight);
		Edge e;
		e.v1 = nodeA;
		e.v2 = nodeB;
		e.weight = weight;
		edges.push_back(e);
	}

	void minimum_spanning_tree_prims(char startNode)
	{
		vector<char> visited;
		int min_span_tree_cost = 0;
		visited.push_back(startNode);
		// Until all vertices have been visited
		while (visited.size() < numVertices)
		{

			int minCost = 1000;
			Edge minCostEdge;
			for (char visitedNode : visited)
			{
				// Find neighbors of visitedNode
				Node *currentNode = HEAD;
				while (currentNode != nullptr)
				{
					if (currentNode->name == visitedNode)
					{
						// Read neighbors
						Node *neighbor = currentNode->next;
						while (neighbor != nullptr)
						{
							if (std::find(visited.begin(), visited.end(), neighbor->name) == visited.end())
							{
								// neighbor not in visited
								if (neighbor->weight < minCost)
								{
									minCostEdge.v1 = currentNode->name;
									minCostEdge.v2 = neighbor->name;
									minCostEdge.weight = neighbor->weight;
									minCost = minCostEdge.weight;
								}
							}
							neighbor = neighbor->next;
						}
						break;
					}
					currentNode = currentNode->down;
				}
			}
			cout << "Edge added: " << minCostEdge.v1 << " " << minCostEdge.v2 << "\n";
			min_span_tree_cost += minCostEdge.weight;
			visited.push_back(minCostEdge.v2);
		}
		cout << "Cost: " << min_span_tree_cost << "\n";
	}

	void print()
	{
		Node *currentNode = HEAD;
		while (currentNode != nullptr)
		{
			cout << currentNode->name << ": ";
			Node *neighbor = currentNode->next;
			while (neighbor != nullptr)
			{
				cout << char(neighbor->name) << "(" << neighbor->weight << ")"
					 << " ";
				neighbor = neighbor->next;
			}
			cout << "\n";
			currentNode = currentNode->down;
		}
	}
};

int main()
{
	Graph g;
	g.addEdge('A', 'B', 4);
	g.addEdge('A', 'C', 6);
	g.addEdge('A', 'D', 2);
	g.addEdge('D', 'C', 3);
	g.addEdge('C', 'B', 2);
	g.addEdge('C', 'E', 4);
	g.addEdge('B', 'E', 1);
	g.print();
	g.minimum_spanning_tree_prims('B');

	return 0;
}
