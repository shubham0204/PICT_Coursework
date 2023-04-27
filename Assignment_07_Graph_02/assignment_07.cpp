#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
	char name ;
	int weight = 0 ;
	Node* next = nullptr ;
	Node* down = nullptr ;
};

struct Edge {
	char v1 ;
	char v2 ;
	int weight ;
};

class Graph {

	Node* HEAD = nullptr ;
	vector<Edge> edges ;
    int numVertices = 0 ; 

	void add( char nodeA , char nodeB , int weight ) {
		if( HEAD == nullptr ) {
			Node* A = new Node() ;
			Node* B = new Node() ;
			A -> name = nodeA ;
			B -> name = nodeB ;
			B -> weight = weight ;
			A -> next = B ;
			HEAD = A;
		}
		else {
			Node* currentNode = HEAD ;
			bool found = false ;
			while( currentNode -> down != nullptr ) {
				if( currentNode -> name == nodeA ) {
					Node* neighbor = currentNode -> next ;
					while( neighbor -> next != nullptr ) {
						neighbor = neighbor -> next ;
					}
					Node* B = new Node() ;
					B -> name = nodeB ;
					B -> weight = weight ;
					neighbor -> next = B ;
					found = true ;
					break ;
				}
				currentNode = currentNode -> down ;
			}
			if( !found ) {
				Node* A = new Node() ;
				Node* B = new Node() ;
				A -> name = nodeA ;
				B -> name = nodeB ;
				B -> weight = weight ;
				A -> next = B ;
				currentNode -> down = A ;
                numVertices++ ;  
			}
		}

	}

public:

	void addEdge( char nodeA , char nodeB , int weight ) {
		add( nodeA , nodeB , weight ) ;
		add( nodeB , nodeA , weight ) ;
		Edge e ;
		e.v1 = nodeA ;
		e.v2 = nodeB ;
		e.weight = weight ;
		edges.push_back( e ) ;
	}

	void minimum_spanning_tree_kruskal( char startNode ) {
		// Sort edges with insertion sort
        int min_span_tree_cost = 0 ; 
		for( int i = 0 ; i < edges.size() ; i++ ) {
			for( int j = i ; j > 0 ; j-- ) {
				if( edges[ j ].weight < edges[ j - 1 ].weight ) {
					Edge temp = edges[ j ] ;
					edges[ j ] = edges[ j - 1 ] ;
					edges[ j - 1 ] = temp ;
				}
			}
		}
		vector<char> visited ;
		visited.push_back( startNode ) ;
        cout << startNode << " " ; 
		for( Edge e : edges ) {
            if( std::find( visited.begin() , visited.end() , e.v1 ) == visited.end() ) {
                visited.push_back( e.v1 ) ; 
                cout << e.v1 << " " ; 
                min_span_tree_cost += e.weight ; 
            }
            if( std::find( visited.begin() , visited.end() , e.v2 ) == visited.end() ) {
                visited.push_back( e.v2 ) ; 
                cout << e.v2 << " " ; 
                min_span_tree_cost += e.weight ; 
            }
		}
        cout << "\n" ; 
        cout << "Cost: " << min_span_tree_cost << "\n" ; 
	}

	void minimum_spanning_tree_prims( char startNode ) {
		vector<char> visited ;
        int min_span_tree_cost = 0 ; 
        visited.push_back( startNode ) ; 
        cout << startNode << " " ;
		while( visited.size() < numVertices - 1 ) {
            int minCost = 1000 ;
			Edge minCostEdge ;
			for( char visitedNode : visited ) {
				// Find neighbors of visitedNode
				Node* currentNode = HEAD ;
				while( currentNode != nullptr ) {
					if( currentNode -> name == visitedNode ) {
						// Read neighbors
						Node* neighbor = currentNode -> next ;
						while( neighbor != nullptr ) {
							if( std::find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
								// neighbor not in visited
								if( neighbor -> weight < minCost ) {
									minCostEdge.v1 = currentNode -> name ;
									minCostEdge.v2 = neighbor -> name ;
									minCostEdge.weight = neighbor -> weight ;
									minCost = neighbor -> weight ;
								}
							}
                            neighbor = neighbor -> next ; 
						}
						break ;
					}
					currentNode = currentNode -> down ;
				}
			}
            cout << minCostEdge.v2 << " " ; 
            min_span_tree_cost += minCostEdge.weight ; 
            visited.push_back( minCostEdge.v2 ) ; 
		}
        cout << "\n" ; 
        cout << "Cost: " << min_span_tree_cost << "\n" ; 
	}

	void print() {
		Node* currentNode = HEAD ;
		while( currentNode != nullptr ) {
			cout << currentNode -> name << ": " ;
			Node* neighbor = currentNode -> next ;
			while( neighbor != nullptr ) {
				cout << char(neighbor -> name) << "(" << neighbor -> weight << ")" << " " ;
				neighbor = neighbor -> next ;
			}
			cout << "\n" ;
			currentNode = currentNode -> down ;
		}
	}

};

int main() {
	Graph g ;
	g.addEdge( 'A' , 'B' , 4 ) ;
	g.addEdge( 'A' , 'C' , 3 ) ;
	g.addEdge( 'A' , 'D' , 2 ) ;
	g.addEdge( 'D' , 'C' , 4 ) ;
	g.addEdge( 'B' , 'C' , 3 ) ;
	g.addEdge( 'C' , 'E' , 5 ) ;
	g.addEdge( 'B' , 'E' , 6 ) ;
	g.minimum_spanning_tree_prims( 'A' ) ;
	g.minimum_spanning_tree_kruskal( 'A' ) ; 

	return 0;
}
