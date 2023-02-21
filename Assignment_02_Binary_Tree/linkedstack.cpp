#include <iostream>
using namespace std ; 

template <class E>
struct StackNode {
    E val ; 
    StackNode* next = nullptr ;
} ; 

template <class E>
class Stack {

    StackNode<E>* TOP ; 
    StackNode<E>* START ; 
    int numElements ;

    public:

    Stack() {
        START = nullptr ; 
        TOP = nullptr ; 
        numElements = 0 ; 
    }

    ~Stack() {
        StackNode<E>* currentNode = new( StackNode<E> ) ; 
        while( currentNode != nullptr ) {
            StackNode<E>* nextNode = currentNode -> next ; 
            delete currentNode ; 
            currentNode = currentNode -> next ; 
        }
        cout << "\n" ; 
    }

    void push( E element ) {
        StackNode<E>* newNode = new( StackNode<E> ) ;
        newNode -> val = element ; 
        if( numElements == 0 ) {
            TOP = newNode ; 
            START = TOP ; 
        }
        else {
            TOP -> next = newNode ; 
            TOP = newNode ; 
        }
        numElements++ ; 
    }

    E pop() {
        StackNode<E>* currentNode = START ; 
        while( currentNode -> next -> next != nullptr ) {
            currentNode = currentNode -> next ; 
        }
        E topVal = TOP -> val ; 
        delete TOP ; 
        TOP = new( StackNode<E> ) ; 
        TOP = currentNode ;
        TOP -> next = nullptr ; 
        numElements-- ;  
        return topVal ;
    }

    void print() {
        StackNode<E>* currentNode = START ; 
        while( currentNode != nullptr ) {
            cout << currentNode -> val << " " ; 
            currentNode = currentNode -> next ; 
        }
        cout << "\n" ; 
    }

    bool isEmpty() {
        return numElements != 0 ; 
    }

} ; 