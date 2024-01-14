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

        friend class Graph ; 
} ;  

class Graph {

    ListNode* head = nullptr ;

    void _add_edge(
            std::string node_a , 
            std::string node_b 
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
            std::string node_b
            ) {
        _add_edge( node_a , node_b ) ;
        _add_edge( node_b , node_a ) ;
        num_edges += 1 ; 
    }

    void dfs_recursive() {
        std::vector<std::string> visited ; 
        stack_neighbors( head , visited ) ;
        std::cout << LBR ; 
    }

    void stack_neighbors(
            ListNode* node , 
            std::vector<std::string>& visited
            ) {
        if( node == nullptr ) return ; 
        std::cout << node -> name << " " ; 
        visited.push_back( node -> name ) ;
        ListNode* n = find_node( node -> name ) ;
        if( n != nullptr ) {
            ListNode* neighbor = n -> next ; 
            while( neighbor != nullptr ) {
                if( std::find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                    stack_neighbors( neighbor , visited ) ; 
                }
                neighbor = neighbor -> next ; 
            } 
        }
    }

    bool goal_test(
            ListNode* node , 
            std::string dst_node
            ) {
        return node -> name == dst_node ; 
    }


    ListNode* dfs_iterative(
            std::string dst_node
            ) {
        // Initial state of the problem -> head node
        ListNode* node = head ; 

        if( goal_test( node , dst_node ) ) return node ; 

        // Frontier/open-list containing nodes which have to
        // expanded
        std::stack<ListNode*> frontier ;

        // closed-list/explored-list containing nodes which have
        // been traversed 
        std::vector<ListNode*> explored ; 
        frontier.push( node ) ; 

        while( true ) {

            if( frontier.empty() ) return nullptr;

            node = frontier.top() ;
            frontier.pop() ;  
            explored.push_back( node ) ;  

            // Expand the frontier by adding
            // nodes/states achieved by performing all possible actions 
            // on the current node (or state)
            // i.e. add all neighbors of the current node to the stack
            ListNode* curr_node = node -> next ; 
            while( curr_node != nullptr ) {
                if( std::find( explored.begin() , explored.end() , curr_node ) == explored.end() ) {
                    if( goal_test( curr_node , dst_node ) ) return curr_node ; 
                    frontier.push( curr_node )  ; 
                }
                curr_node = curr_node -> next ; 
            }

        }

        return nullptr ;  
    }

    void bfs_recursive() {
        std::queue<std::string> queue ; 
        std::vector<std::string> visited ; 
        queue.push( head -> name ) ;
        queue_neighbors( queue , visited ) ;
        std::cout << LBR ; 
    }

    void queue_neighbors(
            std::queue<std::string>& queue , 
            std::vector<std::string> visited 
            ) {
        if( queue.empty() ) return ; 
        std::string curr_node_name = queue.front() ; 
        std::cout << curr_node_name << " " ; 
        queue.pop() ; 
        visited.push_back( curr_node_name ) ;

        ListNode* node = find_node( curr_node_name ) ; 
        if( node != nullptr ) {
            ListNode* neighbor = node -> next ; 
            while( neighbor != nullptr ) {
                if( std::find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                    queue.push( neighbor -> name ) ; 
                }
                neighbor = neighbor -> next ; 
            }
        }
        queue_neighbors( queue , visited ) ; 
    }

    ListNode* bfs_iterative(
            std::string dst_node_name        
            ) {

        // Initial state of the problem
        ListNode* node = head ; 

        if( goal_test( node , dst_node_name ) ) return node ; 

        // Frontier, containing all states which will
        // be expanded
        std::queue<ListNode*> frontier ;

        // explored-list, containing all states which
        // have been expanded 
        std::vector<ListNode*> explored ; 
        frontier.push( node ) ;  

        while( true ) {

            if( frontier.empty() ) return nullptr ; 

            node = frontier.front() ;
            frontier.pop() ;  
            explored.push_back( node ) ;  

            // Expand the frontier
            ListNode* curr_node = node -> next ; 
            while( curr_node != nullptr ) {
                if( std::find( explored.begin() , explored.end() , curr_node ) == explored.end() ) {
                    if( goal_test( curr_node , dst_node_name )) return curr_node ; 
                    frontier.push( curr_node ) ;
                }
                curr_node = curr_node -> next ; 
            } 

        }
     
    }

} ;

int main( int argc , char* argv[] ) {

    Graph g ; 
    g.add_edge( "a" , "b" ) ; 
    g.add_edge( "a" , "c" ) ; 
    g.add_edge( "b" , "d" ) ; 

    std::cout << "Number of nodes: " << g.num_nodes << LBR ; 
    std::cout << "Number of edges: " << g.num_edges << LBR ; 

    std::cout << "Adjacency List" << LBR ; 
    g.print() ; 

    std::string dst_node_name ; 
    std::cout << "Enter node name to search: " << LBR ; 
    std::cin >> dst_node_name ; 
    ListNode* solution = g.dfs_iterative( dst_node_name ) ; 
    if( solution ) {
        std::cout << "Node found -> " << solution << LBR ; 
    }
    else {
        std::cout << "Node not found" << LBR ; 
    }

    solution = g.bfs_iterative( dst_node_name ) ; 
    if( solution ) {
        std::cout << "Node found -> " << solution << LBR ; 
    }
    else {
        std::cout << "Node not found" << LBR ; 
    }

    return 0 ; 
}
