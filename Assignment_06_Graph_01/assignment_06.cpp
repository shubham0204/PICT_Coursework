#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "linkedqueue.cpp"
#include "linkedstack.cpp"
using namespace std ; 

// Represents a node in the linkedlist 
// that is used in the adjacency list
struct Node {
    string name ;          // Name of the vertex
    Node* next = nullptr ; // Pointer to the node representing the linkedlist of neighbors of this vertex
    Node* down = nullptr ; // Pointer to the next head node in the adjacency list
} ; 

class Graph {

private:

Node* HEAD = nullptr ; 

void add( string nodeA , string nodeB ) {
    if( HEAD == nullptr ) {
        // The adjacency list is empty,
        // Initialize HEAD
        Node* newNode1 = new( Node ) ; 
        Node* newNode2 = new( Node ) ; 
        newNode1 -> name = nodeA ;
        newNode2 -> name = nodeB ; 
        // As nodeA and nodeB are neighbors, 
        // nodeA -> next = nodeB
        newNode1 -> next = newNode2 ; 
        HEAD = newNode1 ; 
    }
    else {
        // In the headnodes, search for nodeA
        Node* currentNode = HEAD ; 
        Node* prevNode = nullptr ; 
        bool found = false ; 
        while( currentNode != nullptr ) {
            if( currentNode -> name == nodeA ) {
                // nodeA found, now insert nodeB in the linkedlist of nodeA's neighbors
                found = true ; 
                Node* currentNeighbor = currentNode ; 
                while( currentNeighbor -> next != nullptr ) {
                    currentNeighbor = currentNeighbor -> next ;
                }
                Node* newNode = new( Node ) ; 
                newNode -> name = nodeB ;
                // currentNeighbor is the last element in the linkedlist
                currentNeighbor -> next = newNode ; 
                break ;
            }
            prevNode = currentNode ;
            // Proceed downwards, to the next headnode
            currentNode = currentNode -> down ; 
        }
        if( !found ) {
            // nodeA is absent in the headnodes
            // Create a new headnode and add nodeB to its linkedlist
            // nodeA -> next = nodeB
            Node* newNode1 = new( Node ) ; 
            Node* newNode2 = new( Node ) ; 
            newNode1 -> name = nodeA ;
            newNode2 -> name = nodeB ; 
            prevNode -> down = newNode1 ; 
            newNode1 -> next = newNode2 ;
        }
    }
}

public:

// Add an undirected edge between node1 and node2
void addNode( string node1 , string node2 ) {
    add( node1 , node2 ) ; // add edge from node1 to node2
    add( node2 , node1 ) ; // add edge from node2 to node1
}

// Travel the adjacency list and print the nodes
void print() {
    Node* currentNode = HEAD ; 
    while( currentNode != nullptr ) {
        Node* currentNeighbor = currentNode ;
        while( currentNeighbor != nullptr ) {
            cout << currentNeighbor -> name << " " ; 
            currentNeighbor = currentNeighbor -> next ; 
        }
        cout << "\n" ; 
        currentNode = currentNode -> down ; 
    }
}

// Print the degree of each node
void printDegrees() {
    Node* currentNode = HEAD ; 
    while( currentNode != nullptr ) {
        // currentNode represents the headnode
        Node* currentNeighbor = currentNode ;
        int degree = -1 ;
        // Iterate through all nodes in the linkedlist of `currentNode` and 
        // increment `degree`
        while( currentNeighbor != nullptr ) {
            degree++ ; 
            currentNeighbor = currentNeighbor -> next ; 
        }
        cout << "Degree of node " << currentNode -> name << " is " << degree << "\n"; 
        currentNode = currentNode -> down ; 
    }
}

// Perform breadth-first traversal from node with name = `nodeName`
void breadthFirst( string nodeName ) {
    LinkedQueue<string> queue ; 
    vector<string> visited;         // Maintain an array for visited nodes
    visited.push_back( nodeName ) ; // Add starting node to visited
    queue.push( nodeName ) ;        // Add starting node to queue
    while( true ) {
        // If queue is not empty,
        // pop it and print the resulting node
        // and assign it to `nodeName`
        if( !queue.isEmpty() ) {
            string poppedNode = queue.front() ;
            queue.pop() ; 
            nodeName = poppedNode ; 
            cout << nodeName << " "; 
        }
        else {
            cout << "\n" ; 
            break ;
        }        
        // Append unvisited neighbors of node with name=`nodeName`
        Node* currentNode = HEAD ;
        bool found = false ; 
        while( currentNode != nullptr ) {
            if( currentNode -> name == nodeName ) {
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
            cout << "Starting node does not exist in the graph" << "\n" ; 
            return ; 
        }
    }
}

void depthFirst( string nodeName ) {
    LinkedStack<string> stack ; 
    vector<string> visited; 
    visited.push_back( nodeName ) ;
    stack.push( nodeName ) ; 
    while( true ) {
        if( !stack.isEmpty() ) {
            string poppedNode = stack.top() ; 
            stack.pop() ; 
            nodeName = poppedNode ; 
            cout << nodeName << " "; 
        }
        else {
            cout << "\n" ; 
            break ;
        }   
        Node* currentNode = HEAD ;
        bool found = false ; 
        while( currentNode != nullptr ) {
            if( currentNode -> name == nodeName ) {
                found = true ; 
                Node* neighbor = currentNode -> next ; 
                while( neighbor != nullptr ) {
                    if( find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                        visited.push_back( neighbor -> name ) ;
                        stack.push( neighbor -> name ) ; 
                    }
                    neighbor = neighbor -> next ; 
                }
                break ; 
            }
            currentNode = currentNode -> down ; 
        }
        if( !found ) {
            cout << "Starting node does not exist in the graph" << "\n" ; 
            return ; 
        }     
    }
}

} ;

int main() {
    Graph g ; 
    g.addNode( "Katraj" , "PICT" ) ;
    g.addNode( "Bharti" , "Katraj" ) ; 
    g.addNode( "Bharti" , "PICT" ) ;
    g.addNode( "Katraj" , "SKNCOE" ) ; 
    g.addNode( "PICT" , "SKNCOE" ) ;
    g.addNode( "SKNCOE" , "Temple" ) ; 
    g.addNode( "Temple" , "Katraj" ) ; 
    g.addNode( "Temple" , "Kondwa" ) ; 
    g.print() ; 
    g.printDegrees() ; 
    g.breadthFirst( "Katraj" ) ; 
    g.depthFirst( "Katraj" ) ;
    return 0;
}