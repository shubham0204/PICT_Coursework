#include <iostream>
using namespace std ; 

template <class E>
struct StackNode {
    E val ; 
    StackNode* prev = nullptr ; 
    StackNode* next = nullptr ;
} ; 

template <class E>
class LinkedStack {

    StackNode<E>* TOP ; 
    StackNode<E>* START ; 
    int numElements ;

    public:

    LinkedStack() {
        START = nullptr ; 
        TOP = nullptr ; 
        numElements = 0 ; 
    }

    void push( E element ) {
        StackNode<E>* newNode = new( StackNode<E> ) ;
        newNode -> val = element ; 
        if( numElements == 0 ) {
            TOP = newNode ; 
            START = TOP ; 
        }
        else {
            newNode -> prev = TOP ; 
            TOP -> next = newNode ; 
            TOP = newNode ; 
        }
        numElements++ ; 
    }

    E top() {
        return TOP -> val ;
    }

    void pop() {
        if( numElements >= 2 ) {
            StackNode<E>* newTop = TOP -> prev ; 
            delete TOP ; 
            TOP = new( StackNode<E> ) ; 
            TOP = newTop ;
            TOP -> next = nullptr ;   
        } 
        else {
            delete TOP ; 
        }
        numElements--;
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
        return numElements == 0 ; 
    }

} ; 