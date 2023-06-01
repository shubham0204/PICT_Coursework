
template <class E>
class Stack {

    E arr[ 100 ] ; 
    int top_ = -1 ; 

    public:

    void push( E element ) {
        arr[ ++top_ ] = element ; 
    }

    void pop() {
        top_-- ; 
    }

    E top() {
        return arr[ top_ ] ; 
    }

    bool empty() {
        return top_ == -1 ; 
    }

} ; 
