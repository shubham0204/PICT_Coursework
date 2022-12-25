/*
    Implement C++ program for expression conversion as infix to postfix and its evaluation
    using stack based on given conditions:
    1. Operands and operator, both must be single character.
    2. Input Postfix expression must be in a desired format.
    3. Only '+', '-', '*' and '/ ' operators are expected.
    */
#include <iostream>
using namespace std;

template <class E>
class Stack {

private:
    int HEAD_INDEX = -1;
    E *elements;
    int numElements = 0;
    int capacity = 0;

public:


    Stack(int capacity){
        this -> numElements = 0;
        this -> capacity = capacity;
        elements = new E[capacity];
    }

    void push(E element){
        if( numElements > capacity ) {
            cout << "Stack is full" << "\n" ; 
        }
        else {
            *( elements + ++HEAD_INDEX ) = element ; 
            numElements++ ; 
        }
    }

    E top() {
        return *( elements + HEAD_INDEX ) ; 
    }

    void print() {
        for (int i = numElements - 1; i > -1; i--) {
            cout << *(elements + i) << "\n";
        }
    }

    bool isEmpty() {
        return numElements == 0 ;
    }

    bool isFull() {
        return numElements == capacity ;
    }

    E pop() {
        if (numElements > 0) {
            numElements-- ; 
            return *( elements + HEAD_INDEX-- ) ; 
        }
        else {
            cout << "Stack is empty" << "\n" ;
            return '\0' ; 
        }
    }

    int getNumElements() {
        return numElements ; 
    }

};

int getPrecedence( char c ) {
    if( c == '(' || c == ')' ) {
        return 4 ; 
    }
    else if( c == '^' ) {
        return 3 ; 
    }
    else if( c == '*' || c == '/' ) {
        return 2 ; 
    }
    else if( c == '+' || c== '-' ) {
        return 1 ;
    }
    else {
        return -1 ; 
    }
}

int do_op(char op, int a, int b) {
    switch(op)
    {
    case '+':
       return a+b;
    break;
    case '-':
       return a-b;
    break;
    case '*':
       return a*b;
    break;
    case '/':
       return a/b;
    break;
    default:
        throw std::runtime_error("unknown op") ;
    }
 }

// K+L-M*N+(O^P)*W/U/V*T+Q
// KL+MN*-OP^W*U/V/T*+Q+
int main() {
    string infixExpression , postfixExpression ; 
    cout << "Enter infix expression: " << "\n" ; cin >> infixExpression ; 
    Stack<char> stack( infixExpression.length() ) ;
    for( char c : infixExpression ) {
        if( getPrecedence( c ) == -1 ) {
            // Operand
            postfixExpression += c ; 
        }
        else if( c == '(' ) {
            stack.push( c ) ;
        }
        else if( c == ')' ) {
            while( stack.top() != '(' ) {
                char p = stack.pop() ;
                postfixExpression += p ; 
            }
            stack.pop() ; 
        }
        else {
            while( !stack.isEmpty() && getPrecedence( stack.top() ) >= getPrecedence( c ) ) {
                postfixExpression += stack.top() ; 
                stack.pop() ;
            }
            stack.push( c ) ; 
        }
    }
    
    while( !stack.isEmpty() ) {
        char p = stack.pop() ;
        postfixExpression += p ; 
    }

    cout << "Postfix expression is: " << "\n" ;
    cout << postfixExpression << "\n" ; 
    
    Stack<int> stack2( postfixExpression.length() ) ;
    for( char s : postfixExpression ) {
        if( getPrecedence( s ) == -1 ) {
            stack2.push( s ) ; 
        }
        else {
            int a = (int)stack2.pop() - 48;
            int b = (int)stack2.pop() - 48;
            int res = do_op( s , b , a ) ; 
            stack2.push( res ) ;
        }
    }
    cout << stack2.top() << "\n" ; 
    return 0;
}
