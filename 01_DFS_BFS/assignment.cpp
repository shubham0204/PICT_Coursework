#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;

#define LBR '\n'

class Graph {

    map<string,vector<string>> adjacency_list;
    size_t n_nodes ; 
    size_t n_edges ; 

    public:

    void add_edge( 
        const string& node1 , 
        const string& node2 
    ) {
        if (adjacency_list.count(node1) != 0) {
            adjacency_list[node1].push_back( node2 ) ; 
        }
        else {
            vector<string> node_list ; 
            node_list.push_back( node2 ) ; 
            adjacency_list[node1] = node_list;
        }
        if (adjacency_list.count(node2) != 0) {
            adjacency_list[node2].push_back( node1 ) ; 
        }
        else {
            vector<string> node_list ; 
            node_list.push_back( node1 ) ; 
            adjacency_list[node2] = node_list;
        }
    }

    void print() {
        for (const pair<string,vector<string>>& node_list: adjacency_list ) {
            cout << node_list.first << " : " ; 
            for (const string& neighbor: node_list.second ) {
                cout << neighbor << " " ; 
            }
            cout << LBR ; 
        }
    }

    void depth_search(
        const string& key , 
        const string& start_node 
    ) {
        vector<string> visited ; 
        depth_search_impl( start_node , key , visited , 0 ) ;
    }

    bool depth_search_impl( 
        const string& node , 
        const string& key , 
        vector<string>& visited ,
        size_t level
    ) {
        cout << "[DFS] Visited " << node << " , level = " << level << LBR ; 
        if (node == key) {
            cout << key << " found in the graph!" << LBR ; 
            return true;
        }
        visited.push_back( node ) ; 
        vector<string> neighbors = adjacency_list[node] ; 
        for (const string& neighbor: neighbors) {
            if ( find( visited.begin() , visited.end() , neighbor) == visited.end() ) {
                bool found = depth_search_impl( neighbor , key , visited , level + 1 ) ;  
                if (found) return true; 
            }
        }
        return false; 
    }

    void breadth_search(
        const string& key , 
        const string& start_node 
    ) {
        vector<string> visited ; 
        queue<string> frontier ; 
        queue<size_t> frontier_levels ; 
        frontier.push( start_node ) ;
        frontier_levels.push( 0 ) ; 
        breadth_search_impl( frontier , frontier_levels , key , visited ) ;
    }

    void breadth_search_impl( 
        queue<string>& frontier , 
        queue<size_t>& frontier_levels , 
        const string& key , 
        vector<string>& visited 
    ) {
        if (frontier.size() == 0) return ;
        string node = frontier.front() ;
        size_t level = frontier_levels.front() ; 
        cout << "[BFS] Visited " << node << " , level = " << level << LBR ;  
        frontier.pop() ; 
        frontier_levels.pop() ; 
        if (node == key) {
            cout << key << " found in the graph!" << LBR ; 
        }
        visited.push_back( node ) ; 
        vector<string> neighbors = adjacency_list[node] ; 
        for (const string& neighbor: neighbors) {
            if ( find( visited.begin() , visited.end() , neighbor) == visited.end() ) {
                frontier.push( neighbor ) ; 
                frontier_levels.push( level + 1 ) ;
            }
        }
        breadth_search_impl( frontier , frontier_levels , key , visited ) ;  
    }


} ;

string input( string message ) {
    cout << message << LBR ; 
    string line ;
    cin >> line ; 
    return line ;
} ; 

int main( int argc , char* argv[] ) {
    Graph graph ; 
    cout << "Enter node-pairs:" << LBR ; 
    while (true) {
        string node1 = input( "Node 1" ) ; 
        string node2 = input( "Node 2" ) ;  
        if (node1 == "-" && node2 == "-") {
            break ;
        }
        graph.add_edge( node1 , node2 ) ;
        cout << "[Edge from " << node1 << " to " << node2 << " added]" << LBR ; 
    }
    string key = input( "Enter key: " ) ;
    string start_node = input( "Enter start node: " ) ; 
    graph.depth_search( key , start_node ) ; 
    graph.breadth_search( key , start_node ) ; 
    graph.print() ; 
}