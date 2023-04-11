#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "linkedqueue.cpp"
#include "linkedstack.cpp"
using namespace std ; 

struct Node {
    string name ; 
    Node* next = nullptr ; 
    Node* down = nullptr ;
} ; 

class Graph {

private:

Node* HEAD = nullptr ; 

void add( string nodeA , string nodeB ) {
    if( HEAD == nullptr ) {
        Node* newNode1 = new( Node ) ; 
        Node* newNode2 = new( Node ) ; 
        newNode1 -> name = nodeA ;
        newNode2 -> name = nodeB ; 
        newNode1 -> next = newNode2 ; 
        HEAD = newNode1 ; 
    }
    else {
        Node* currentNode = HEAD ; 
        Node* prevNode = nullptr ; 
        bool found = false ; 
        while( currentNode != nullptr ) {
            if( currentNode -> name == nodeA ) {
                found = true ; 
                Node* currentNeighbor = currentNode ; 
                while( currentNeighbor -> next != nullptr ) {
                    currentNeighbor = currentNeighbor -> next ;
                }
                Node* newNode = new( Node ) ; 
                newNode -> name = nodeB ;
                currentNeighbor -> next = newNode ;
                break ;
            }
            prevNode = currentNode ; 
            currentNode = currentNode -> down ; 
        }

        if( !found ) {
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

void addNode( string node1 , string node2 ) {
    add( node1 , node2 ) ; 
    add( node2 , node1 ) ;
}

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

void printDegrees() {
    Node* currentNode = HEAD ; 
    while( currentNode != nullptr ) {
        Node* currentNeighbor = currentNode ;
        int degree = -1 ;
        while( currentNeighbor != nullptr ) {
            degree++ ; 
            currentNeighbor = currentNeighbor -> next ; 
        }
        cout << "Degree of node " << currentNode -> name << " is " << degree << "\n"; 
        currentNode = currentNode -> down ; 
    }
}

void breadthFirst( string nodeName ) {
    LinkedQueue<Node*> queue ; 
    vector<string> visited; 
    while( true ) {
        Node* currentNode = HEAD ;
        bool found = false ; 
        while( currentNode != nullptr ) {
            if( currentNode -> name == nodeName ) {
                found = true ; 
                Node* neighbor = currentNode -> next ; 
                while( neighbor != nullptr ) {
                    if( find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                        visited.push_back( neighbor -> name ) ;
                        queue.push( neighbor ) ; 
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
        if( !queue.isEmpty() ) {
            Node* poppedNode = queue.front() ;
            queue.pop() ; 
            nodeName = poppedNode -> name ; 
            cout << nodeName << " "; 
        }
        else {
            cout << "\n" ; 
            break ;
        }        
    }
}

void depthFirst( string nodeName ) {
    LinkedStack<Node*> stack ; 
    vector<string> visited; 
    while( true ) {
        Node* currentNode = HEAD ;
        bool found = false ; 
        while( currentNode != nullptr ) {
            if( currentNode -> name == nodeName ) {
                found = true ; 
                Node* neighbor = currentNode -> next ; 
                while( neighbor != nullptr ) {
                    if( find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                        visited.push_back( neighbor -> name ) ;
                        stack.push( neighbor ) ; 
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
        if( !stack.isEmpty() ) {
            Node* poppedNode = stack.top() ; 
            stack.pop() ; 
            nodeName = poppedNode -> name ; 
            cout << nodeName << " "; 
        }
        else {
            cout << "\n" ; 
            break ;
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