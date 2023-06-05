#include "linkedqueue.cpp"
#include <iostream>
using namespace std ; 

class Node {

    int val ; 
    Node* left = nullptr ; 
    Node* right = nullptr ; 

    public:

    friend class OptimalBST ; 

} ; 

// References:
// 1. https://youtu.be/vLS-zRCHo-Y
// 2. https://github.com/crpatil1901/Sem3Assignments/blob/main/DSAL/assignment8.cpp
// 3. https://www.geeksforgeeks.org/optimal-binary-search-tree-dp-24/

// The code is highly inspired from Abdul Bari's video
// """""""""""""""""""""""""""""""""""""""""""""
// PLEASE WATCH THIS BEFORE READING THE CODE -> https://youtu.be/vLS-zRCHo-Y
// THE CODE BELOW WORKS ONLY FOR 4 NODES
// """""""""""""""""""""""""""""""""""""""""""""

class OptimalBST {

    int R[ 100 ][ 100 ] ; 
    int C[ 100 ][ 100 ] ; 

    // Denotes the function 'w'
    // arr -> freqs (frequencies)
    // low -> 'i'
    // high -> 'j'
    // The function returns w( i , j )
    int subarray_sum( int arr[] , int low , int high ) {
        int sum = 0 ; 
        for( int i = low ; i < high ; i++ ) {
            sum += arr[ i ] ; 
        }
        return sum ;
    }

    // Find an optimal subtree given that the subtrees should be 
    // made of 'n' nodes
    // The cost of each subtree is maintained in the matrix C
    // The root of each subtree is maintained in the matrix R
    void findOptimalSubtree( int freqs[] , int numNodesInSubtree , int n ) {

        // Use the formula:
        // C[ i , j ] = min{ C[ i , k-1 ] + C[ k , j ] } + w( i , j )
        // Range for k is: i < k <= j

        for( int i = 0 ; i < n - numNodesInSubtree ; i++ ) {
            int j = i + numNodesInSubtree ; 
            // Here, we need to use the formula mentioned in
            // the beginning of this method
            int minCost = 1e+8 ; 
            int minCostRoot = R[ i ][ j - 1 ] ; 
            for( int k = i + 1 ; k <= j ; k++ ) {
                int cost = C[ i ][ k - 1 ] + C[ k ][ j ] ;
                if( cost < minCost ) {
                    minCost = cost ; 
                    minCostRoot = k ; 
                }
            }
            C[ i ][ j ] = minCost + subarray_sum( freqs , i , j ) ; 
            R[ i ][ j ] = minCostRoot ; 
        }

    }


    public:

    Node* ROOT = nullptr ;

    void findOBST( int values[] , int freqs[] , int totalNodes ) {
        int n = totalNodes + 1 ; 

        // Denotes the matrix C and set all 
        // entries to zero
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                C[ i ][ j ] = 0;
            }
        }

        // Denotes the matrix R which contains
        // values of roots
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                R[ i ][ j ] = 0;
            }
        }

        // Step 1 -> 
        // Set diagonal elements to 0
        // C_ii = 0 for all 0 <= i <= n
        for( int i = 0 ; i < n ; i++ ) {
            C[ i ][ i ] = 0 ; 
        }

        // Step 2 -> 
        // Compute cost for all BSTs made up of 1 node
        // i.e. C_ij such that (j - i) = 1
        for( int i = 0 ; i < n - 1 ; i++ ) {
            int j = i + 1 ; 
            C[ i ][ j ] = freqs[ i ] ; 
            R[ i ][ j ] = j ; 
        }

        // Step 3 ->
        // Compute cost for all BSTs made up of 2 nodes
        // to (n-1) nodes
        for( int i = 2 ; i < n ; i++ ) {
            findOptimalSubtree( freqs , i , n ) ;
        }

        // (Optional) Print the matrix R
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                cout.width( 5 ) ; 
                cout << R[ i ][ j ] << " " ; 
            }
            cout << "\n" ; 
        }

        // (Optional) Print the matrix C
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                cout.width( 5 ) ; 
                cout << C[ i ][ j ] << " " ; 
            }
            cout << "\n" ; 
        }
        cout << "Cost of OBST is " << C[ 0 ][ n - 1 ] << "\n" ; 

        // Step 4 -> 
        // Construct the OBST with cost matrix C and roots matrix R ready
        ROOT = new( Node ) ; 
        ROOT = constructOBST( 0 , n - 1  , values ) ; 
    }

    Node* constructOBST( int i , int j , int values[] ) { 
        if( i == j ) {
            return nullptr ; 
        }
        else {
            Node* p = new( Node ) ; 
            p -> val = values[ R[ i ][ j ] - 1 ] ; 
            p -> left = constructOBST( i , R[i][j] - 1, values ) ; 
            p -> right = constructOBST( R[i][j] , j , values ) ; 
            return p ; 
        }
    }

    void inorder(Node* node) {
        if( node == nullptr ) {
            return;
        }
        inorder( node -> left ) ;
        cout << node -> val << " " ; 
        inorder( node -> right ) ;
    }

    void preorder(Node* node) {
        if( node == nullptr ) {
            return;
        }
        cout << node -> val << " " ;
        preorder( node -> left ) ;
        preorder( node -> right ) ;
    }

} ;

int main() {
    OptimalBST tree ; 
    cout << "Enter number of values: " << "\n" ; 
    int totalNodes = 0 ; cin >> totalNodes ; 
    int values[ totalNodes ] ;
    int freqs[ totalNodes ] ; 
    for( int i = 0 ; i < totalNodes ; i++ ) {
        cout << "Enter value: " << "\n" ; 
        cin >> values[ i ] ; 
        cout << "Enter frequency: " << "\n" ; 
        cin >> freqs[ i ] ; 
    }
    tree.findOBST( values , freqs , totalNodes ) ;  
    tree.inorder( tree.ROOT ) ;
    tree.preorder( tree.ROOT ) ; 
    return 0 ; 
}