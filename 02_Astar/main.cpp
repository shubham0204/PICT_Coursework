#include <iostream>
#include <queue>
#include <string>
#include <stack>
#include <algorithm>

#define LBR '\n'

class ListNode {
    public:

    std::string name = "";
    ListNode* next = nullptr ;
    ListNode* down = nullptr ;
    int weight = 0 ; 

    friend class Graph ; 
} ;  

class Graph {

    ListNode* head = nullptr ;

    void _add_edge(
        std::string node_a , 
        std::string node_b , 
        int weight 
    ) {
        if( head == nullptr ) {
            head = new( ListNode ) ; 
            head -> name = node_a ; 
            head -> next = new( ListNode ) ; 
            head -> next -> name = node_b ; 
            num_nodes += 1 ; 
        }
        else {
            ListNode* node = find_node( node_a ) ; 
            if( node != nullptr ) {
                while( node -> next != nullptr ) {
                    node = node -> next ; 
                }
                node -> next = new( ListNode ) ; 
                node -> next -> name = node_b ; 
            }
            else {
                node = head ; 
                while( node -> down != nullptr ) {
                    node = node -> down ; 
                }
                node -> down = new( ListNode ) ; 
                node -> down -> name = node_a ; 
                node -> down -> next = new( ListNode ) ; 
                node -> down -> next -> name = node_b ; 
                num_nodes += 1 ; 
            }    
        }
    }

    ListNode* find_node(
        std::string name
    ) {
        ListNode* current_node = head ; 
        while( current_node != nullptr ) {
            if( current_node -> name == name ) {
                return current_node ; 
            }
            current_node = current_node -> down ; 
        }
        return nullptr ; 
    }

    

    public:

    size_t num_nodes = 0; 
    size_t num_edges = 0;

    void print() {
        ListNode* curr_node_down = head ; 
        while( curr_node_down != nullptr ) {
            ListNode* curr_node = curr_node_down ; 
            while( curr_node != nullptr ) {
                std::cout << curr_node -> name << " " ;
                curr_node = curr_node -> next ; 
            }
            std::cout << LBR ; 
            curr_node_down = curr_node_down -> down ; 
        }
    }

    void add_edge(
        std::string node_a , 
        std::string node_b , 
        int weight
    ) {
        _add_edge( node_a , node_b , weight ) ;
        _add_edge( node_b , node_a , weight ) ;
        num_edges += 1 ; 
    }

    float shortest_path(
        std::string src_node , 
        std::string dst_node , 
        std::vector<std::string>& path
    ) {
        std::vector<std::string> open_list ;
        std::vector<std::string> closed_list ;

        open_list.push_back( src_node ) ;  

        while( !open_list.empty() ) {

        }
    }

} ;

int main( int argc , char* argv[] ) {

    Graph g ; 
    g.add_edge( "a" , "b" , 2 ) ; 
    g.add_edge( "a" , "c" , 3 ) ; 
    g.add_edge( "b" , "d" , 1 ) ; 

    std::cout << "Number of nodes: " << g.num_nodes << LBR ; 
    std::cout << "Number of edges: " << g.num_edges << LBR ; 

    std::cout << "Adjacency List" << LBR ; 
    g.print() ; 

    return 0 ; 
}