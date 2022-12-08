#include <iostream>
#include <string>
using namespace std ; 

/*
Implementation of a Circular Queue
The basic concept of FIFO is followed, but the difference is that
FRONT and REAR index pointers are not constrained within the bounds of the array 
but can assume any positive integral value.
To make sure FRONT and REAR are within the bounds of the array, we use modified index pointers,
FRONT' = FRONT % capacity
REAR' = REAR % capacity
*/
template <class E>
class CircularQueue {

private:

int FRONT ;        // For deletion
int REAR ;         // For insertion
int capacity ;     // Number of elements that can be stored in the queue
int numElements ;  // Maximum elements that the queue can hold
E* elements ;      // Array of `E` to store the elements

public:

CircularQueue( int capacity ) ; // Constructor to initialize `elements`
~CircularQueue() ;              // Destructor to deallocate `elements`
void enqueue( E element ) ;     // Insertion of `element`
E deque() ;                     // Pop/deque `front` and return the element
bool isEmpty() ;                // Check if queue is empty
bool isFull() ;                 // Check if queue is full
E front() ;                     // Returns element at `front`
E rear() ;                      // Returns element at `rear`
void print() ;                  // Prints the contents of the queue

} ; 

template <class E>
CircularQueue<E>::CircularQueue( int capacity ) : capacity( capacity ) {
    elements = new E[ capacity ] ; 
    FRONT = REAR = -1 ; 
    numElements = 0 ; 
}

template <class E>
CircularQueue<E>::~CircularQueue() {
    delete elements ; 
}

template <class E>
void CircularQueue<E>::enqueue( E element ) {
    if( !isFull() ) {
        if( numElements == 0 ) {
            FRONT++ ; // FRONT becomes 0
        }
        // Increment REAR and set `element` in elements[ REAR ] 
        elements[ ++REAR % capacity ] = element ; 
        numElements++ ; 
    }
    else {
        cout << "The queue has reached its maximum capacity" << "\n" ; 
    }
}

template <class E>
E CircularQueue<E>::deque() {
    if( !isEmpty() ) {
        numElements-- ; 
        return elements[ FRONT++ % capacity ];
    }
    else {
        cout << "The queue is empty" << "\n" ; 
        return NULL ; 
    }
}

template <class E>
bool CircularQueue<E>::isEmpty() {
    return numElements == 0 ; 
}

template <class E>
bool CircularQueue<E>::isFull() {
    return numElements == capacity ;
}

template <class E>
E CircularQueue<E>::front() {
    if( !isEmpty() ) {
        return elements[ FRONT ] ; 
    }
    else {
        cout << "The queue is empty" << "\n" ; 
    }
}

template <class E>
E CircularQueue<E>::rear() {
    if( !isEmpty() ) {
        return elements[ REAR ] ; 
    }
    else {
        cout << "The queue is empty" << "\n" ; 
    }
}

template <class E>
void CircularQueue<E>::print() {
    if( !isEmpty() ) {
        for( int i = FRONT ; i < FRONT + numElements ; i++ ) {
            cout << elements[ i % capacity ] << " " ;
        }
        cout << "\n" ; 
    }
    else {
        cout << "The queue is empty" << "\n" ; 
    }
}


int main() {
    int capacity ; 
    cout << "Enter total number of tasks: " << "\n" ; cin >> capacity ; 
    CircularQueue<string> queue( capacity ) ; 

    while( true ) {
        cout << "Enter a option:" << "\n" ; 
        cout << "1. Schedule a Task" << "\n" ; 
        cout << "2. Execute a Task" << "\n" ; 
        cout << "3. Print all tasks" << "\n" ; 
        cout << "4. Exit" << "\n" ; 
        int option ; cin >> option ; 
        if( option == 1 ) {
            char message[ 50 ] ; 
            cout << "Enter task description: " << "\n" ;
            cin.getline( &message[0] , sizeof( message ) , ';' ) ;
            queue.enqueue( string( message ) ) ; 
        }
        else if( option == 2 ) {
            cout << "Task " << queue.deque() << " executed" << "\n" ; 
        } 
        else if( option == 3 ) {
            queue.print() ; 
        }
        else if( option == 4 ) {
            break; 
        }
    }
    return 0 ; 
}