#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std ; 

class Node {

    char val ; 
    Node* next = nullptr ; 
    Node* down = nullptr ; 

    public:

    friend class Graph ; 

} ;

class Graph {

    Node* HEAD = nullptr ; 

    void addElement( char v1 , char v2 ) {
        if( HEAD == nullptr ) {
            HEAD = new( Node ) ; 
            HEAD -> val = v1 ; 
            HEAD -> next = new( Node ) ; 
            HEAD -> next -> val = v2 ; 
        }
        else {
            Node* headCurrent = HEAD ; 
            Node* prevHead = nullptr ; 
            bool found = false ; 
            while( headCurrent != nullptr ) {
                if( headCurrent -> val == v1 ) {
                    found = true ; 
                    Node* n = headCurrent ; 
                    while( n -> next != nullptr ) {
                        n = n -> next ; 
                    }
                    n -> next = new( Node ) ; 
                    n -> next -> val = v2 ; 
                }
                prevHead = headCurrent ; 
                headCurrent = headCurrent -> down ; 
            }
            if( !found ) {
                Node* newNode = new( Node ) ; 
                newNode -> val = v1 ; 
                newNode -> next = new( Node ) ; 
                newNode -> next -> val = v2 ; 
                prevHead -> down = newNode ; 
            }
        }
    }

    public:

    void addEdge( char v1 , char v2 ) {
        addElement( v1 , v2 ) ; 
        addElement( v2 , v1 ) ; 
    }

    void print() {
        Node* headCurrent = HEAD ; 
        while( headCurrent != nullptr ) {
            Node* n = headCurrent ; 
            cout << n -> val << " : "  ;
            while( n != nullptr ) {
                cout << n -> val << " - " ; 
                n = n -> next ; 
            }
            cout << "\n" ; 
            headCurrent = headCurrent -> down ; 
        }
    }

    void bfs( char start ) {
        vector<char> visited ; 
        visited.push_back( start ) ; 
        queue<char> q ; 
        q.push( start ) ; 
        while( !q.empty() ) {
            char p = q.front() ; 
            q.pop() ; 
            cout << p << " " ; 
            Node* headCurrent = HEAD ; 
            while( headCurrent != nullptr ) {
                if( headCurrent -> val == p ) {
                    Node* n = headCurrent ; 
                    while( n != nullptr ) {
                        if( std::find( visited.begin() , visited.end() , n -> val ) == visited.end() ) {
                            q.push( n -> val ) ; 
                            visited.push_back( n -> val ) ;
                        }
                        n = n -> next ; 
                    }
                    break ; 
                }
                headCurrent = headCurrent -> down ; 
            }
        }
        cout << "\n" ; 
    }

    void dfs( char start ) {
        vector<char> visited ; 
        visited.push_back( start ) ; 
        stack<char> s ; 
        s.push( start ) ; 
        while( !s.empty() ) {
            char p = s.top() ; 
            s.pop() ; 
            cout << p << " " ; 
            Node* headCurrent = HEAD ; 
            while( headCurrent != nullptr ) {
                if( headCurrent -> val == p ) {
                    Node* n = headCurrent ; 
                    while( n != nullptr ) {
                        if( std::find( visited.begin() , visited.end() , n -> val ) == visited.end() ) {
                            s.push( n -> val ) ; 
                            visited.push_back( n -> val ) ;
                        }
                        n = n -> next ; 
                    }
                    break ; 
                }
                headCurrent = headCurrent -> down ; 
            }
        }
        cout << "\n" ; 
    }


} ; 

int main() {

    Graph g ; 
    g.addEdge( 'a' , 'b' ) ; 
    g.addEdge( 'b' , 'c' ) ; 
    g.addEdge( 'a' , 'c' ) ;
    g.print() ; 

    g.bfs( 'a' ) ; 
    g.dfs( 'a' ) ; 

    return 0 ;
}