
template <class E>
class Queue {

    int arrSize = 100 ; 
    E arr[ 100 ] ; 
    int front_ = -1 ; 
    int rear = -1 ; 

    public:

    void push( E element ) {
        arr[ ++rear ] = element ; 
        if( front_ == -1 ) {
            front_ = 0 ; 
        }
    }

    void pop() {
        front_++; 
    }

    E front() {
        return arr[ front_ ] ; 
    }

    bool empty() {
        return front_ > rear ; 
    }

} ; 