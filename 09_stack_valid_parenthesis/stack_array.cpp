#include <iostream>
using namespace std;

template <class E>
class Stack {

private:
    int HEAD_INDEX;
    E *elements;
    int numElements;
    int capacity;

public:


    Stack(int capacity){
        // Initialize array
        this -> numElements = 0;
        this -> capacity = capacity;
        elements = new E[capacity];
    }

    void push(E element){
        if (numElements == 0){
            HEAD_INDEX = 0;
            *(elements + HEAD_INDEX) = element;
        }
        else{
            HEAD_INDEX++;
            *(elements + HEAD_INDEX) = element;
        }
        numElements += 1;
    }

    void print() {
        for (int i = numElements - 1; i > -1; i--) {
            cout << *(elements + i) << "\n";
        }
    }

    void pop() {
        if (numElements > 0) {
            HEAD_INDEX -= 1;
            numElements -= 1;
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
    stack.print() ; 


    return 0;
}