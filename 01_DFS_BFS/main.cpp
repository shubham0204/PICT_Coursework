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
            ListNode* curr_node_down = head ; 
            ListNode* curr_node_prev = nullptr ; 
            bool is_found = false ; 
            while( curr_node_down != nullptr ) {
                if( curr_node_down -> name == node_a ) {
                    ListNode* curr_node = curr_node_down ; 
                    while( curr_node -> next != nullptr ) {
                        curr_node = curr_node -> next ; 
                    }
                    curr_node -> next = new( ListNode ) ; 
                    curr_node -> next -> name = node_b ; 
                    is_found = true ; 
                    break ;
                }
                curr_node_prev = curr_node_down ; 
                curr_node_down = curr_node_down -> down ; 
            }
            if( !is_found ) {
                curr_node_prev -> down = new( ListNode ) ; 
                curr_node_prev -> down -> name = node_a ; 
                curr_node_prev -> down -> next = new( ListNode ) ; 
                curr_node_prev -> down -> next -> name = node_b ; 
                num_nodes += 1 ; 
            }
        }
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
        ListNode* curr_node_down = head ; 
        while( curr_node_down != nullptr ) {
            if( curr_node_down -> name == node -> name ) {
                ListNode* neighbor = curr_node_down -> next ; 
                while( neighbor != nullptr ) {
                    if( std::find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                        stack_neighbors( neighbor , visited ) ; 
                    }
                    neighbor = neighbor -> next ; 
                } 
                break ; 
            }
            curr_node_down = curr_node_down -> down ; 
        }
    }

    void dfs_iterative() {

        std::stack<std::string> s ; 
        std::vector<std::string> visited ; 
        s.push( head -> name ) ; 

        while( !s.empty() ) {

            std::string curr_node_name = s.top() ; 
            std::cout << curr_node_name << " " ;
            visited.push_back( curr_node_name ) ;  
            s.pop() ;

            ListNode* curr_node_down = head ; 
            while( curr_node_down != nullptr ) {
                if( curr_node_down -> name == curr_node_name ) {
                    ListNode* curr_node = curr_node_down -> next ; 
                    while( curr_node != nullptr ) {
                        if( std::find( visited.begin() , visited.end() , curr_node -> name ) == visited.end() ) {
                            s.push( curr_node -> name ) ; 
                        }
                        curr_node = curr_node -> next ; 
                    } 
                    break ; 
                }
                curr_node_down = curr_node_down -> down ; 
            }
           
        }
        std::cout << LBR ; 
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
        ListNode* curr_node_down = head ; 
        while( curr_node_down != nullptr ) {
            if( curr_node_down -> name == curr_node_name ) {
                ListNode* neighbor = curr_node_down -> next ; 
                while( neighbor != nullptr ) {
                    if( std::find( visited.begin() , visited.end() , neighbor -> name ) == visited.end() ) {
                        queue.push( neighbor -> name ) ; 
                    }
                    neighbor = neighbor -> next ; 
                } 
                break ; 
            }
            curr_node_down = curr_node_down -> down ; 
        }
        queue_neighbors( queue , visited ) ; 
    }

    void bfs_iterative() {
        std::queue<std::string> q ; 
        std::vector<std::string> visited ; 
        q.push( head -> name ) ; 

        while( !q.empty() ) {

            std::string curr_node_name = q.front() ; 
            std::cout << curr_node_name << " " ;
            visited.push_back( curr_node_name ) ;  
            q.pop() ;

            ListNode* curr_node_down = head ; 
            while( curr_node_down != nullptr ) {
                if( curr_node_down -> name == curr_node_name ) {
                    ListNode* curr_node = curr_node_down -> next ; 
                    while( curr_node != nullptr ) {
                        if( std::find( visited.begin() , visited.end() , curr_node -> name ) == visited.end() ) {
                            q.push( curr_node -> name ) ; 
                        }
                        curr_node = curr_node -> next ; 
                    } 
                    break ; 
                }
                curr_node_down = curr_node_down -> down ; 
            }
           
        }
        std::cout << LBR ;
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

    std::cout << "DFS Iterative" << LBR ; 
    g.dfs_iterative() ;

    std::cout << "DFS Recursive" << LBR ; 
    g.dfs_recursive() ; 
    
    std::cout << "BFS Iterative" << LBR ; 
    g.bfs_iterative() ; 

    std::cout << "BFS Recursive" << LBR ;  
    g.bfs_recursive() ; 

    return 0 ; 
}