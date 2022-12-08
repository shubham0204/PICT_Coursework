#include <iostream>
using namespace std;

template <class E>
class DoubleEndedQueue {

private:

int FRONT ;
int REAR ;
int numElements ; 
int capacity ; 
E* elements ; 

public:

DoubleEndedQueue( int capacity ) ;
~DoubleEndedQueue() ;
void enqueueRear( E element ) ; 
void enqueueFront( E element ) ;
E dequeFront() ;
E dequeRear() ; 

bool isEmpty() ; 
bool isFull() ; 

E front() ; 
E rear() ; 

void print() ;

};

template <class E>
DoubleEndedQueue<E>::DoubleEndedQueue( int capacity ) : capacity( capacity ) {
    elements = new E[ capacity ] ; 
    FRONT = REAR = -1 ; 
    numElements = 0 ; 
}

template <class E>
DoubleEndedQueue<E>::~DoubleEndedQueue() {
    delete elements ; 
}

template <class E>
void DoubleEndedQueue<E>::enqueueRear( E element ) {
    if( !isFull() ) {
        if( numElements == 0 ) {
            FRONT++ ;
        }
        elements[ ++REAR % capacity ] = element ; 
        numElements++ ; 
    }
    else {
        cout << "The queue has reached its maximum capacity" << "\n" ; 
    }
}

template <class E>
void DoubleEndedQueue<E>::enqueueFront( E element ) {
    if( !isFull() ) {
        if( numElements == 0 ) {
            // first element
            FRONT++ ; // 0
        }
        cout << --FRONT % capacity << " sfsdf " << "\n" ; 
        elements[ --FRONT % capacity ] = element ;
        cout << FRONT % capacity << " sfsdf222 " << "\n" ;  
        cout << elements[ -1 ] << "\n" ;
        numElements++ ; 
    }
    else {
        cout << "The queue has reached its maximum capacity" << "\n" ; 
    }
}

template <class E>
E DoubleEndedQueue<E>::dequeFront() {
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
E DoubleEndedQueue<E>::dequeRear() {
    if( !isEmpty() ) {
        numElements-- ; 
        return elements[ REAR-- % capacity ];
    }
    else {
        cout << "The queue is empty" << "\n" ; 
        return NULL ; 
    }
}

template <class E>
bool DoubleEndedQueue<E>::isEmpty() {
    return numElements == 0 ; 
}

template <class E>
bool DoubleEndedQueue<E>::isFull() {
    return numElements == capacity ;
}

template <class E>
E DoubleEndedQueue<E>::front() {
    if( !isEmpty() ) {
        return elements[ FRONT ] ; 
    }
    else {
        cout << "The queue is empty" << "\n" ; 
    }
}

template <class E>
E DoubleEndedQueue<E>::rear() {
    if( !isEmpty() ) {
        return elements[ REAR ] ; 
    }
    else {
        cout << "The queue is empty" << "\n" ; 
    }
}

template <class E>
void DoubleEndedQueue<E>::print() {
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
    cout << "Enter capacity of deque: " << "\n" ; cin >> capacity ;
    DoubleEndedQueue<int> queue( capacity ) ;

    while( true ) {
        cout << "Enter a option:" << "\n" ; 
        cout << "1. Enqueue to front" << "\n" ; 
        cout << "2. Enqueue to rear" << "\n" ; 
        cout << "3. Deque from front" << "\n" ; 
        cout << "4. Deque from rear" << "\n" ; 
        cout << "5. Exit" << "\n" ; 
        int option ; cin >> option ; 
        if( option == 1 ) {
            int element ; 
            cout << "Enter element for insertion: " ; cin >> element ; 
            queue.enqueueFront( element ) ;
            cout << " >>> " ; 
            queue.print() ; 
        }
        else if( option == 2 ) {
            int element ; 
            cout << "Enter element for insertion: " ; cin >> element ; 
            queue.enqueueRear( element ) ;
            cout << " >>> " ; 
            queue.print() ; 
        } 
        else if( option == 3 ) {
            queue.dequeFront() ; 
            cout << " >>> " ; 
            queue.print() ;
        }
        else if( option == 4 ) {
            queue.dequeRear() ; 
            cout << " >>> " ; 
            queue.print() ;
        }
        else if( option == 5 ) {
            break; 
        }
    }



    return 0;
}