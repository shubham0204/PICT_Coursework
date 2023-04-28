#include <iostream>
#include <vector>
#include "linkedqueue.cpp"
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
			numVertices++ ;
		}
		else {
			Node* currentNode = HEAD ;
			bool found = false ;
			Node* prevNode = nullptr ;
			while( currentNode != nullptr ) {
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
				prevNode = currentNode ;
				currentNode = currentNode -> down ;
			}
			if( !found ) {
				Node* A = new Node() ;
				Node* B = new Node() ;
				A -> name = nodeA ;
				B -> name = nodeB ;
				B -> weight = weight ;
				A -> next = B ;
				prevNode -> down = A ;
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

	// Perform breadth-first traversal from node with name = `nodeName`
	bool isCycle( char nodeA , char nodeB ) {
	    LinkedQueue<char> queue ;
	    vector<char> visited;
	    visited.push_back( nodeA ) ;
	    queue.push( nodeA ) ;
	    char currentNodeName = nodeA ;
	    while( true ) {
	        // If queue is not empty,
	        // pop it and print the resulting node
	        // and assign it to `nodeName`
	        if( !queue.isEmpty() ) {
	            char poppedNode = queue.front() ;
	            queue.pop() ;
	            currentNodeName = poppedNode ;
	            //cout << currentNodeName << " " ;
	            if( currentNodeName == nodeB ) {
	            	return true ;
	            }
	        }
	        else {
	            break ;
	        }
	        // Append unvisited neighbors of node with name=`nodeName`
	        Node* currentNode = HEAD ;
	        bool found = false ;
	        while( currentNode != nullptr ) {
	            if( currentNode -> name == currentNodeName ) {
	                found = true ;
	                Node* neighbor = currentNode -> next ;
	                while( neighbor != nullptr ) {
	                    if( find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
	                        visited.push_back( neighbor -> name ) ;
	                        queue.push( neighbor -> name ) ;
	                    }
	                    neighbor = neighbor -> next ;
	                }
	                break ;
	            }
	            currentNode = currentNode -> down ;
	        }
	        if( !found ) {
	            //cout << "Starting node does not exist in the graph" << "\n" ;
	            return false;
	        }
	    }
	}


	void minimum_spanning_tree_kruskal( char startNode ) {
		// Sort edges with insertion sort
		Graph g ;
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
		for( Edge e : edges ) {
			if( !g.isCycle( e.v1 , e.v2 ) ) {
				g.addEdge( e.v1 , e.v2 , e.weight ) ;
				if( std::find( visited.begin() , visited.end() , e.v1 ) == visited.end() ) {
					visited.push_back( e.v1 ) ;
				}
				if( std::find( visited.begin() , visited.end() , e.v2 ) == visited.end() ) {
					visited.push_back( e.v2 ) ;
				}
				min_span_tree_cost += e.weight ;
				cout << "Edge added: " << e.v1 << " " << e.v2 << "\n" ;
			}

		}
        cout << "Cost: " << min_span_tree_cost << "\n" ;
	}

	void minimum_spanning_tree_prims( char startNode ) {
		vector<char> visited ;
        int min_span_tree_cost = 0 ;
        visited.push_back( startNode ) ;
        // Until all vertices have been visited
		while( visited.size() < numVertices ) {

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
									minCost = minCostEdge.weight ;
								}
							}
                            neighbor = neighbor -> next ;
						}
						break ;
					}
					currentNode = currentNode -> down ;
				}
			}
			//cout << "Min Cost " << minCost << "\n" ;
            cout << "Edge added: " << minCostEdge.v1 << " " << minCostEdge.v2 << "\n" ;
            min_span_tree_cost += minCostEdge.weight ;
            visited.push_back( minCostEdge.v2 ) ;
		}
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
	g.addEdge( 'A' , 'C' , 6 ) ;
	g.addEdge( 'A' , 'D' , 2 ) ;
	g.addEdge( 'D' , 'C' , 3 ) ;
	g.addEdge( 'C' , 'B' , 2 ) ;
	g.addEdge( 'C' , 'E' , 4 ) ;
	g.addEdge( 'B' , 'E' , 1 ) ;
	g.print() ;
	g.minimum_spanning_tree_prims( 'A' ) ;
	g.minimum_spanning_tree_kruskal( 'A' ) ;

	return 0;
}
