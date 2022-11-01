#include <iostream>
using namespace std ;

// LinkedList implementation
class LinkedList {

protected:

    // Node structure
    struct Node {
        // Value that the node contains
        int value ;
        // Pointer to the next node in the list
        Node* pointerToNext = nullptr;
    } ;

    // Pointer to Node representing the start of the list
    Node* START ;

    // Pointer to Node representing the last element of the list
    Node* HEAD ;
    
    int numElements;

public:

    LinkedList(){
        START = nullptr ; 
        HEAD = nullptr ; 
        numElements = 0 ; 
    }
    ~LinkedList() ;

    void insertFront(int element ) ;
    void insertBack(int element) ;
    void insertAt( int element , int index ) ;
    int get( int index ) ;
    void deleteByValue( int value ) ;
    void deleteByIndex( int index ) ;
    void print() ;
    void clear() ;
} ;

LinkedList::~LinkedList(){
    // When this object is destructed, free all the nodes
    clear() ;
}

void LinkedList::insertFront(int element ) {
    if ( numElements == 0 ) {
        // If the list was empty, initialize START and HEAD
        START = new( Node ) ;
        START -> value = element ;
        HEAD = START;
    }
    else {
        // Else, update HEAD
        Node* headNode = HEAD ;
        Node* nextNode = new( Node ) ;
        nextNode -> value = element ;
        headNode -> pointerToNext = nextNode ;
        HEAD = nextNode ;
    }
    numElements += 1 ;
}

void LinkedList::insertBack(int element) {
    if ( numElements == 0 ) {
        START = new( Node ) ;
        START -> value = element ;
        HEAD = START;
    }
    else {
        Node* firstNode = START ;
        Node* nextNode = new( Node ) ;
        nextNode -> value = element ;
        nextNode -> pointerToNext = firstNode ;
        START = nextNode ;
    }
    numElements += 1 ;
}

void LinkedList::insertAt(int element, int index) {
    Node* currentNode = START ;
    for ( int i = 0 ; i < index ; i ++ ) {
        currentNode = currentNode -> pointerToNext ;
    }
    Node* newNode = new( Node ) ;
    newNode -> value = element ;
    newNode -> pointerToNext = currentNode -> pointerToNext ;
    currentNode -> pointerToNext = newNode ;
    numElements += 1 ;
}

int LinkedList::get( int index ) {
    Node* currentNode = START ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        if( index == i ) {
            return currentNode -> value ;
        }
        currentNode = currentNode -> pointerToNext ;
    }
    return -1 ;
}

void LinkedList::deleteByIndex( int index ) {
    // kth Node in the LinkedList
    Node* prevNode = START ;

    // (k+1)th Node in the LinkedList
    Node* currentNode = START ;

    for ( int i = 0 ; i < numElements ; i ++ ) {
        // Checking if value == currentNode's value
        if ( i == index ) {
            if( i == 0 ) {
                // Delete first element START of the LinkedList
                // and reassign it
                START = START -> pointerToNext ;
            }
            else if ( i == numElements - 1 ) {
                // Delete last element HEAD of the LinkedList
                // and reassign it
                delete HEAD ;
                HEAD = new( Node ) ;
                HEAD = prevNode ;
            }
            else {
                prevNode -> pointerToNext = currentNode -> pointerToNext ;
            }
            numElements -= 1 ;
            break;
        }
        prevNode = currentNode ;
        currentNode = currentNode -> pointerToNext ;
    }
}

void LinkedList::deleteByValue( int value ) {
    // kth Node in the LinkedList
    Node* prevNode = START ;

    // (k+1)th Node in the LinkedList
    Node* currentNode = START ;

    for ( int i = 0 ; i < numElements ; i ++ ) {
        // Checking if value == currentNode's value
        if ( (currentNode -> value) == value ) {
            if( i == 0 ) {
                // Delete first element START of the LinkedList
                // and reassign it
                START = START -> pointerToNext ;
            }
            else if ( i == numElements - 1 ) {
                // Delete last element HEAD of the LinkedList
                // and reassign it
                delete HEAD ;
                HEAD = new( Node ) ;
            }
            break;
        }
        prevNode = currentNode ;
        currentNode = currentNode -> pointerToNext ;
    }
}

void LinkedList::print() {
    Node* currentNode = START ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        std::cout << currentNode -> value << " " ;
        currentNode = currentNode -> pointerToNext ;
    }
}

void LinkedList::clear() {
    // Delete all dynamically allocated nodes to free up memory
    Node* currentNode = START ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        Node* nextNode = currentNode -> pointerToNext ;
        delete currentNode ;
        currentNode = nextNode ;
    }
    numElements = 0 ;
    START = nullptr ;
    HEAD = nullptr ;
}

int main() {
    LinkedList list ; 
    list.insertFront( 56 ) ; 
    list.insertFront( 60 ) ; 
    list.print() ; 

    return 0;
}