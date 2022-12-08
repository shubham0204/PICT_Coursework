#include <iostream>
using namespace std ; 

template <class E>
class PriorityQueue {

private:

struct Node {
    E val ; 
    int priority ; 
    Node* next ; 
} ;
Node* FRONT ; 
Node* REAR ; 
int numElements = 0 ; 

public:

void enqueue( E element , int priority ) {
    if( isEmpty() ) {
        FRONT = new( Node ) ; 
        FRONT -> val = element ; 
        FRONT -> priority = priority ; 
        FRONT -> next = nullptr ; 
        REAR = FRONT ; 
    }
    else {
        if( REAR -> priority >= priority ) {
            Node* newNode = new( Node ) ; 
            newNode -> val = element ; 
            newNode -> priority = priority ; 
            newNode -> next = nullptr ; 
            REAR -> next = newNode ; 
            REAR = newNode ; 
        }
        else if( priority > FRONT -> priority ) {
            Node* newNode = new( Node ) ; 
            newNode -> next = FRONT ; 
            newNode -> val = element ; 
            newNode -> priority = priority ; 
            FRONT = newNode ; 
        }
        else {
            Node* currentNode = FRONT ;
            Node* prevNode = FRONT ; 
            while( currentNode -> priority >= priority ) {
                prevNode = currentNode ; 
                currentNode = currentNode -> next ; 
            }
            Node* newNode = new( Node ) ;
            newNode -> val = element ; 
            newNode -> priority = priority ;
            newNode -> next = currentNode ; 
            prevNode -> next = newNode ;
        }
    }
    numElements++ ; 
}

E deque() {
    Node* nextNode = FRONT -> next ; 
    E val = FRONT -> val ;
    delete FRONT ; 
    FRONT = new( Node ) ;
    FRONT = nextNode ; 
    numElements-- ;
    return val ; 
}

void print() {
    Node* currentNode = FRONT ; 
    while( currentNode != nullptr ) {
        cout << currentNode -> val << " " ; 
        currentNode = currentNode -> next ; 
    }
    cout << "\n" ;
}

bool isEmpty() {
    return numElements == 0 ;
}


} ;

int main() {

    PriorityQueue<int> queue  ; 
    queue.enqueue( 12 , 100 ) ; 
    queue.enqueue( 4 , 200 ) ; 
    queue.enqueue( 5 , 67 ) ; 
    queue.enqueue( 7 , 20 ) ; 

    queue.deque() ; 
    queue.print() ;

    return 0;
}