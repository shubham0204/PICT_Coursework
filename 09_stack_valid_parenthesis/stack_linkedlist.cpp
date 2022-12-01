#include <iostream>
#include "linkedlist.cpp"
using namespace std;

template <class E>
class Stack {

private:
    int HEAD_INDEX;
    LinkedList<E> list ; 
    int numElements;
    int capacity;

public:


    Stack(int capacity){
        // Initialize array
        this -> numElements = 0;
        this -> capacity = capacity;
    }

    void push(E element){
        if (numElements == 0){
            HEAD_INDEX = 0;
        }
        else{
            HEAD_INDEX++;
        }
        list.insertFront( element ) ;
        numElements += 1;
    }

    void print() {
        list.print() ; 
    }

    void pop() {
        if (numElements > 0) {
            numElements -= 1;
            list.deleteByIndex( HEAD_INDEX ) ; 
            HEAD_INDEX -= 1;
        }
    }

    int getNumElements() {
        return numElements ; 
    }

};

int main() {
    char input[50]; 
    cout << "Enter input string: " << "\n" ; 
    cin >> input ; 

    Stack<char> stack( 50 ) ; 

    for( char p : input ) {
        if( p == '{' ) {
            stack.push( p ) ;
        }
        else if( p == '[' ) {
            stack.push( p ) ;
        }
        else if( p == '(' ) {
            stack.push( p ) ;
        }
        else if( p == '}' ) {
            stack.pop( ) ;
        }
        else if( p == ']' ) {
            stack.pop( ) ;
        }
        else if( p == ')' ) {
            stack.pop( ) ;
        }
    }

    if( stack.getNumElements() != 0 ) {
        cout << "Invalid parenthesis" << "\n" ; 
    }
    else {
        cout << "Valid parenthesis" << "\n" ; 
    }

    return 0;
}