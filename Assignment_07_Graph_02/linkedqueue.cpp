#include <iostream>
using namespace std ; 

template <class E>
struct QueueNode {
    E val ; 
    QueueNode* next = nullptr ;
} ; 

template <class E>
class LinkedQueue {

    QueueNode<E>* HEAD ; 
    QueueNode<E>* TAIL ; 
    int numElements ; 

    public:

    LinkedQueue() {
        HEAD = nullptr ; 
        numElements = 0 ;
    }

    ~LinkedQueue() {
        QueueNode<E>* currentNode = HEAD ; 
        while( currentNode != nullptr ) {
            QueueNode<E>* nextNode = currentNode -> next ; 
            delete currentNode ; 
            currentNode = nextNode ; 
        }
    }

    void push( E element ) {
        QueueNode<E>* newNode = new( QueueNode<E> ) ; 
        newNode -> val = element ; 
        if( numElements == 0 ) {
            HEAD = newNode ; 
            TAIL = HEAD ; 
        }
        else {
            TAIL -> next = newNode ; 
            TAIL = newNode ; 
        }
        numElements++ ; 
    }

    E front() {
        return HEAD -> val ;
    }

    void pop() {
        QueueNode<E>* nextNode = HEAD -> next ; 
        delete HEAD ; 
        HEAD = nextNode ; 
        numElements-- ; 
    }

    void print() {
        QueueNode<E>* currentNode = HEAD ; 
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