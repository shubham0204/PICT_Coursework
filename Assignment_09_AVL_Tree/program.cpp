#include <iostream>
#include <cmath>
#include <cstring>
#include "linkedqueue.cpp"
using namespace std ; 

struct Node {
    int key ; 
    string value ; 
    int height = 1 ;       // Default height of a node w.r.t its parent would be one
    Node* left = nullptr ; 
    Node* right = nullptr ; 
} ; 


class AVLTree {

Node* ROOT = nullptr ; 

int getHeight( Node* node ) {
    if( node == nullptr ) {
        return 0;
    }
    return node -> height ; 
}

int getBalanceFactor( Node* node ) {
    // Balance factor is the difference between the heights of the left
    // subtree and right subtree w.r.t to node
    if( node == nullptr ) {
        return 0 ; 
    }
    return getHeight( node -> left ) - getHeight( node -> right ) ; 
}

void updateHeight( Node* node ) {
    node -> height = 1 + max( getHeight( node -> left ) , getHeight( node -> right ) )  ; 
}

Node* LLRotation( Node* node ) {

    Node* newRoot = node -> left ;
    node -> left = newRoot -> right ; 
    newRoot -> right = node;

    // Updating the heights of node and newRoot
    // to in-turn update balance factors of these nodes
    updateHeight( node ) ; 
    updateHeight( newRoot ) ; 

    cout << "[Performed LL Rotation]" << "\n" ;
    return newRoot ;  
}

Node* RRRotation( Node* node ) {

    Node* newRoot = node -> right ; 
    node -> right = newRoot -> left ; 
    newRoot -> left = node ; 

    // Updating the heights of node and newRoot
    // to in-turn update balance factors of these nodes
    updateHeight( node ) ;
    updateHeight( newRoot ) ;

    cout << "[Performed RR Rotation]" << "\n" ;
    return newRoot ; 
}

Node* rotateRL( Node* node ) {
    node -> right = LLRotation( node -> right ) ; 
    return LLRotation( node ) ; 
}

Node* rotateLR( Node* node ) {
    node -> left = RRRotation( node -> left ) ; 
    return RRRotation( node ) ; 
}

Node* balance( Node* node ) {
    if( getBalanceFactor( node ) == 2 ) {
        // Left subtree has a greater height
        // Possible rotations: LL, LR
        if( getBalanceFactor( node -> left ) < 0 ) {
            // For left child, right subtree has greater height. Hence, use LR rotation
            node = rotateLR( node ) ;
        }
        else {
            // For left child, left subtree has greater height. Hence, use LL rotation
            node = LLRotation( node ) ;
        }
    }
    else if( getBalanceFactor( node ) == -2 ) {
        // Right subtree has a greater height
        // Possible rotations: RR, RL
        if( getBalanceFactor( node -> right ) > 0 ) {
            // For left child, right subtree has greater height. Hence, use RL rotation
            node = rotateRL( node ) ;
        }
        else {
            // For left child, left subtree has greater height. Hence, use RR rotation
            node = RRRotation( node ) ; 
        }
    }
    updateHeight( node ) ; 
    return node ; 
}

void inorderRecursive( Node* curr ) {
    if( curr == nullptr ) {
        return ; 
    }
    inorderRecursive( curr -> left ) ; 
    cout << curr -> key << " " ; 
    inorderRecursive( curr -> right ) ; 
}

Node* insertSubTree( Node* curr , int key , string value ) {
    if( curr == nullptr ) {
        Node* newNode = new Node() ; 
        newNode -> key = key ; 
        newNode -> value = value ; 
        return newNode ; 
    }
    if( curr -> key > key ) {
        curr -> left = insertSubTree( curr -> left , key , value ) ; 
    }
    else if( curr -> key < key ) {
        curr -> right = insertSubTree( curr -> right , key , value ) ; 
    }
    else {
        curr -> value = value ; 
        return curr ;
    }
    return balance( curr ) ; 
}

public:

void insert( int key , string value ) {
    ROOT = insertSubTree( ROOT , key , value ) ;
}

void inorder() {
    inorderRecursive( ROOT ) ; 
    cout << "\n" ; 
}

Node* search( int key ) {
    Node* curr = ROOT ; 
    while( curr != nullptr ) {
        if( curr -> key > key ) {
            curr = curr -> left ; 
        }
        else if( curr -> key < key ) {
            curr = curr -> right ; 
        }
        else {
            return curr ; 
        }
    }
    return nullptr ; 
}

void BFS() {
    LinkedQueue<Node*> q ; 
    q.push( ROOT ) ; 
    while( !q.isEmpty() ) {
        Node* poppedNode = q.front() ; 
        cout << poppedNode -> key << " " ; 
        q.pop() ;
        if( poppedNode -> left != nullptr ) {
            q.push( poppedNode -> left ) ; 
        }
        if( poppedNode -> right != nullptr ) {
            q.push( poppedNode -> right ) ;
        }
    }
    cout << "\n" ; 
}

} ;


int main() {
    AVLTree tree ; 
    while( true ) {
        int option ; 
        cout << "Enter option: " << "\n" ; 
        cout << "1. Insert key, value" << "\n" ; 
        cout << "2. Inorder traversal" << "\n" ;
        cout << "3. Search" << "\n" ;
        cout << "4. Exit" << "\n" ;
        cout << "5. BFS" << "\n" ;
        cin >> option ; 
        if( option == 1 ) {
            int key ; 
            cout << "Enter key: " << "\n" ; cin >> key ; 
            string value ; 
            cout << "Enter value: " << "\n" ; cin >> value ; 
            tree.insert( key , value ) ; 
        }
        else if( option == 2 ) {
            cout << "Inorder traversal -> " ;
            tree.inorder() ; 
        }
        else if( option == 3 ) {
            int key ; 
            cout << "Enter key to search: " << "\n" ; cin >> key ; 
            Node* result = tree.search( key ) ; 
            if( result == nullptr ) {
                cout << "Key not found" << "\n" ; 
            }
            else {
                cout << "Key found, value is " << result -> value << "\n" ; 
            }
        }
        else if( option == 4 ){
            break ; 
        }
        else if( option == 5 ) {
            cout << "BFS traversal is " ; 
            tree.BFS() ; 
        }
    }

    return 0 ; 
}