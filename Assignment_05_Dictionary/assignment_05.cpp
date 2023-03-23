#include <iostream>
#include <cstring>
using namespace std ; 


template <class V>
struct Node {
    V val ; 
    Node* next = nullptr ; 
} ; 

template <class V>
class Dictionary {

    Node<V>** headNodes ; 
    int currentSize ;
    int tableSize ; 
    
    int hash( int identifier ) {
        return identifier % tableSize ; 
    }

    void insertNode( Node<V>* headNode , V value ) {
        Node<V>* currentNode = headNode ; 
        while( currentNode -> next != nullptr ) {
            currentNode = currentNode -> next ; 
        }
        Node<V>* newNode = new( Node<V> ) ;
        newNode -> next = nullptr ; 
        newNode -> val = value ; 
        currentNode -> next = newNode ; 
    }

    void printLinkedList( Node<V>* headNode ) {
        Node<V>* currentNode = headNode ; 
        while( currentNode != nullptr ) {
            cout.width( 20 ) ; 
            cout << currentNode -> val << " " ; 
            currentNode = currentNode -> next ; 
        }
    }

    public:

    Dictionary( int tableSize ) {
        this -> tableSize = tableSize ; 
        headNodes = new Node<V>*[ tableSize ] ; 
        for( int i = 0 ; i < tableSize ; i++ ) {
            headNodes[ i ] = nullptr ; 
        }
    }

    void insert( int key , V value ) { 
        int hashAddress = hash( key ) ; 
        if( headNodes[ hashAddress ] == nullptr ) {
            Node<V>* newNode = new( Node<V> ) ; 
            newNode -> next = nullptr ; 
            newNode -> val = value ; 
            headNodes[ hashAddress ] = newNode ; 
        }
        else {
            insertNode( headNodes[ hashAddress ] , value ) ; 
        }
    }

    void display() {
        for( int i = 0 ; i < tableSize ; i++ ) {
            cout.width( 5 ) ;
            cout << i << " " ; 
            printLinkedList( headNodes[ i ] ) ; 
            cout << "\n" ; 
        }
    }

} ; 

int main() {

    Dictionary<string> dict( 10 ) ; 
    dict.insert( 0 , "Hello World" ) ;
    dict.insert( 0 , "Hello World Shubham" ) ; 
    dict.display() ; 

    return 0 ; 
}