#include <iostream>
using namespace std ; 

class DoublyLinkedList {

private:

    // Node structure
    struct Node {
        // Value that the node contains
        int value ;
        // Pointer to the next node in the list
        Node* pointerToNext = nullptr;
        Node* pointerToPrev = nullptr ;
    } ;

    Node* HEAD_FRONT ;
    Node* HEAD_BACK ;
    int numElements ;

    int invert( int x );

public:

    DoublyLinkedList() ;
    ~DoublyLinkedList() ;
    void insertFront( int element ) ;
    void insertBack( int element ) ;
    void printForward() ;
    void printReverse() ;
    void clear() ;

    int getNumElements() ;

    void print1SComplement() ;
    void print2SComplement() ; 
    void printSum( DoublyLinkedList other ) ;

};

DoublyLinkedList::DoublyLinkedList() {
    HEAD_FRONT = nullptr ;
    HEAD_BACK = nullptr ;
    numElements = 0 ;
}

DoublyLinkedList::~DoublyLinkedList() {
    clear() ; 
}

int DoublyLinkedList::getNumElements() {
    return numElements ; 
}

void DoublyLinkedList::insertFront(int element) {
    if ( numElements == 0 ) {
        HEAD_FRONT = new( Node ) ;
        HEAD_FRONT -> value = element ;
        HEAD_BACK = HEAD_FRONT;
    }
    else {
        Node* headNode = HEAD_FRONT ;
        Node* nextNode = new( Node ) ;
        nextNode -> value = element ;
        nextNode -> pointerToPrev = headNode ;
        headNode -> pointerToNext = nextNode ;
        HEAD_FRONT = nextNode ;
    }
    numElements += 1 ;
}

void DoublyLinkedList::insertBack(int element) {
    if ( numElements == 0 ) {
        HEAD_FRONT = new( Node ) ;
        HEAD_FRONT -> value = element ;
        HEAD_BACK = HEAD_FRONT;
    }
    else {
        Node* headNode = HEAD_BACK ;
        Node* nextNode = new( Node ) ;
        nextNode -> value = element ;
        nextNode -> pointerToNext = headNode ;
        headNode -> pointerToPrev = nextNode ;
        HEAD_BACK = nextNode ;
    }
    numElements += 1 ;
}

void DoublyLinkedList::printForward() {
    Node* currentNode = HEAD_BACK ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        std::cout << currentNode -> value << " " ;
        currentNode = currentNode -> pointerToNext ;
    }
    cout << endl ; 
}

void DoublyLinkedList::printReverse() {
    Node* currentNode = HEAD_FRONT ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        std::cout << currentNode -> value << " " ;
        currentNode = currentNode -> pointerToPrev ;
    }
    cout << endl ;
}

void DoublyLinkedList::clear() {
    // Delete all dynamically allocated nodes to free up memory
    Node* currentNode = HEAD_BACK ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        Node* nextNode = currentNode -> pointerToNext ;
        delete currentNode ;
        currentNode = nextNode ;
    }
    numElements = 0 ;
    HEAD_FRONT = nullptr ;
    HEAD_BACK = nullptr ;
}

void DoublyLinkedList::print1SComplement() {
    // Similar to printReverse()
    Node* currentNode = HEAD_FRONT ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        int inv = invert( currentNode -> value ) ; 
        cout << inv << " " ; 
        currentNode = currentNode -> pointerToPrev ;
    }
    cout << endl ;
}

void DoublyLinkedList::print2SComplement() {
    Node* currentNode = HEAD_BACK ;
    int output[ numElements ] ;
    int carry = 1 ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        int inv = invert( currentNode -> value ) ; 
        if( inv + carry > 1 ) {
            output[ i ] = 0 ;
            carry = 1 ; 
        }
        else {
            output[ i ] = inv + carry ; 
            carry = 0 ; 
        }
        currentNode = currentNode -> pointerToNext ;
    }
    for( int i = numElements - 1 ; i >= 0 ; i-- ) {
        cout << output[ i ] << " " ; 
    }
    cout << endl ; 
    cout << "Carry out = " << carry << endl ; 
    cout << endl ; 
}

void DoublyLinkedList::printSum( DoublyLinkedList other ) {
    Node* currentNode1 = HEAD_BACK ;
    Node* currentNode2 = other.HEAD_BACK ; 
    int output[ numElements ] ;
    int carry = 0 ;
    for ( int i = 0 ; i < numElements ; i ++ ) {
        int bit1 = currentNode1 -> value ; 
        int bit2 = currentNode2 -> value ; 
        if( bit1 + bit2 + carry == 2 ) {
            output[ i ] = 0 ;
            carry = 1 ; 
        }
        else if( bit1 + bit2 + carry == 3 ) {
            output[ i ] = 1 ;
            carry = 1 ; 
        }
        else {
            output[ i ] = bit1 + bit2 + carry ; 
            carry = 0 ; 
        }
        currentNode1 = currentNode1 -> pointerToNext ;
        currentNode2 = currentNode2 -> pointerToNext ;
    }
    for( int i = numElements - 1 ; i >= 0 ; i-- ) {
        cout << output[ i ] << " " ; 
    }
    cout << endl ; 
    cout << "Carry out = " << carry << endl ; 
    cout << endl ; 
}

int DoublyLinkedList::invert( int x ) {
    if( x == 1 ) {
        return 0 ; 
    }
    else {
        return 1 ; 
    }
}


DoublyLinkedList takeInput( int i , int numBits = 32 ) {
    int num ; 
    cout << "Enter decimal number " << i << " : " << "\n" ;
    cin >> num ; 
    int quotient = num ;
    DoublyLinkedList number ; 
    while( quotient != 0 ) {
        int bit = quotient % 2 ; 
        number.insertFront( bit ) ; 
        quotient = ( int ) ( quotient / 2 ) ; 
    }
    while( number.getNumElements() != numBits ) {
        number.insertFront( 0 ) ; 
    }
    return number ; 
}


int main() {

    DoublyLinkedList num1 = takeInput( 1 ) ; 
 
    cout << "1st Binary number is ( MSB -> LSB ) : " << endl ; 
    num1.printReverse() ;

    cout << "1s complement is : " << endl ; 
    num1.print1SComplement() ;

    cout << "2s complement is : " << endl ; 
    num1.print2SComplement() ; 

    DoublyLinkedList num2 = takeInput( 2 ) ; 
    
    cout << "2nd Binary number is ( MSB -> LSB ) : " << endl ; 
    num2.printReverse() ;

    cout << "Sum of 1st and 2nd binary number : " << endl ; 
    num2.printSum( num1 ) ;

    return 0;
}

