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

    public:

    Node* ROOT = nullptr ;

    void findOBST( int values[] , int freqs[] , int len ) {
        int n = len + 1 ;  

        // Use the formula:
        // C[ i , j ] = min{ C[ i , k-1 ] + C[ k , j ] } + w( i , j )
        // Range for k is: i < k <= j

        // Denotes the matrix C and set all 
        // entries to zero
        int C[ n ][ n ] ; 
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
        // i.e. C_ij such that (j - i) = 2
        for( int i = 0 ; i < n - 2 ; i++ ) {
            int j = i + 2 ; 
            cout << " i: " << i << " j: " << j << "\n" ; 
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

        // Step 4 -> 
        // Compute cost for all BSTs made up of 3 nodes
        // i.e. C_ij such that (j - i) = 3
        for( int i = 0 ; i < n - 3 ; i++ ) {
            int j = i + 3 ; 
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

        // Step 5 ->
        // Compute cost for all BSTs made up of 4 nodes
        // i.e. C_ij such that (j - i) = 4
        // Only one pair of ( i , j ) is possible
        // which is ( 0 , 4 )
        int i = 0 ;
        int j = 4 ; 
        // Here, we need to use the formula mentioned in
        // the beginning of this method
        int minCost = 1e+8 ; 
        int minCostRoot = R[ i ][ j - 1 ] ;
        for( int k = i + 1 ; k <= j ; k++ ) {
            int cost = C[ i ][ k - 1 ] + C[ k ][ j ] ;
            if( cost < minCost ) {
                minCostRoot = k ; 
                minCost = cost ; 
            }
        }
        C[ i ][ j ] = minCost + subarray_sum( freqs , i , j ) ; 
        R[ i ][ j ] = minCostRoot ; 
    

        // (Optional) Print the matrix C
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                cout.width( 5 ) ; 
                cout << C[ i ][ j ] << " " ; 
            }
            cout << "\n" ; 
        }
        cout << "Cost of OBST: " << C[ 0 ][ n - 1 ] << "\n" ;

        // (Optional) Print the matrix R
        for( int i = 0 ; i < n ; i++ ) {
            for( int j = 0 ; j < n ; j++ ) {
                cout.width( 5 ) ; 
                cout << R[ i ][ j ] << " " ; 
            }
            cout << "\n" ; 
        } 

        ROOT = new( Node ) ; 
        ROOT = constructOBST( 0 , n - 1  , values ) ; 

    }

    Node* constructOBST( int i , int j , int values[] ) { 
        cout << i << " " << j << "\n" ; 
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

} ;

int main() {
    OptimalBST tree ; 
    int values[ 4 ] = { 10 , 20 , 30 , 40 } ; 
    int freqs[ 4 ] = { 4 , 2 , 6 , 3 } ;
    tree.findOBST( values , freqs , 4 ) ;  
    tree.inorder( tree.ROOT ) ;
    return 0 ; 
}