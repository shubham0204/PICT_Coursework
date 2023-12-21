#include <iostream>
#include <queue>
#include <stack>

class ListNode {
    public:

    std::string name = "";
    ListNode* next = nullptr ;
    ListNode* down = nullptr ;

    friend class Graph ; 
} ;  

class Graph {

    ListNode* head = nullptr ;
    size_t num_nodes = 0; 
    size_t num_edges = 0;

    void _add_edge(
        std::string node_a , 
        std::string node_b
    ) {
        if( head == nullptr ) {
            head = new( ListNode ) ; 
            head -> name = node_a ; 
            head -> next = new( ListNode ) ; 
            head -> next -> name = node_b ; 
        }
        else {
            ListNode* curr_node_down = head ; 
            while( curr_node_down != nullptr ) {
                if( curr_node_down -> name == node_a ) {
                    ListNode* curr_node = curr_node_down -> next ; 
                    if( curr_node == nullptr ) {
                        curr_node_down -> next = new( ListNode ) ;
                        curr_node_down -> next -> name = node_a ; 
                    }
                    else {
                        while( curr_node -> next != nullptr ) {
                            curr_node = curr_node -> next ; 
                        }
                        curr_node -> next = new( ListNode ) ; 
                        curr_node -> next -> name = node_b ; 
                    }
                    break ;
                }
                curr_node_down = curr_node_down -> down ; 
            }
        }
    }

    public:

    void add_edge(
        std::string node_a , 
        std::string node_b
    ) {
        _add_edge( node_a , node_b ) ;
        _add_edge( node_b , node_a ) ;
    }

} ;

int main( int argc , char* argv[] ) {

    return 0 ; 
}