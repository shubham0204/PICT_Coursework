#include <iostream>
using namespace std;

class Graph {

    int numVertices = 0 ; 
    int adjacencyMatrix[ 20 ][ 20 ] ; 

    public:

    void readGraph() {
        cout << "Enter no. of vertices" << "\n" ;
        cin >> numVertices ; 
        for( int i = 0 ; i < numVertices ; i++ ) {
            for( int j = 0 ; j < numVertices ; j++ ) {
                cin >> adjacencyMatrix[ i ][ j ] ; 
            }
        }
    }

    void printGraph() {
        for( int i = 0 ; i < numVertices ; i++ ) {
            for( int j = 0 ; j < numVertices ; j++ ) {
                cout << adjacencyMatrix[ i ][ j ] << " " ; 
            }
            cout << "\n" ; 
        }
    }

    void prims() {

        int selectedVertices[ numVertices ] ; 
        for( int i = 0 ; i < numVertices ; i++ ) {
            selectedVertices[ i ] = 0 ;
        }
        selectedVertices[ 0 ] = 1 ; 

        int n = 0 ;
        while( n < numVertices - 1 ) {

            int min_edge_weight = 9999 ; 
            int edge_v1 = 0 ; 
            int edge_v2 = 0 ;

            for( int i = 0 ; i < numVertices ; i++ ) {
                if( selectedVertices[i] == 1 ) {
                    for( int j = 0 ; j < numVertices ; j++ ) {
                        if( selectedVertices[j] == 0 && adjacencyMatrix[i][j] != 0 ) {
                            if( min_edge_weight > adjacencyMatrix[i][j] ) {
                                min_edge_weight = adjacencyMatrix[i][j] ; 
                                edge_v1 = i ; 
                                edge_v2 = j ; 
                            }
                        }
                    }
                }
            }

            cout << "Edge added between " << edge_v1 << " - " << edge_v2 << "\n" ; 
            selectedVertices[ edge_v2 ] = 1 ; 
            n += 1 ; 

        }
    }


} ;


int main() {

    Graph graph ; 
    graph.readGraph() ; 
    graph.printGraph() ; 

    graph.prims() ; 


    return 0 ; 
}