#include <iostream>
using namespace std;

class ThreadedNode {
    int val ; 
    ThreadedNode* left = nullptr ; 
    ThreadedNode* right = nullptr ; 
    int lbit = 0 ; // 0 -> Thread, 1 -> Child
    int rbit = 0 ; // 0 -> Thread, 1 -> Child
    friend class ThreadedBST ; 
} ; 

class ThreadedBST {

    ThreadedNode* HEAD ; 
    ThreadedNode* ROOT ; 

    public:

    void create( int rootValue ) ; 
    void insert( int value ) ; 

    ThreadedNode* inorderSuccessor( ThreadedNode* node ) ; 
    void inorder() ; 
    void preorder() ; 

    void deleteChildNode( ThreadedNode* parentNode , ThreadedNode* childNode ) ;
    void deleteNode( int value ) ; 

} ; 

void ThreadedBST::create( int rootValue ) {
    ThreadedNode* newNode = new( ThreadedNode ) ;
    newNode -> val = rootValue ; 

    HEAD = new( ThreadedNode ) ; 
    HEAD -> val = 0 ; 
    HEAD -> rbit = 1 ; 
    HEAD -> lbit = 1 ; 
    HEAD -> right = HEAD ;

    newNode -> rbit = 0 ; 
    newNode -> lbit = 0 ; 
    newNode -> right = HEAD ; 
    newNode -> left = HEAD ; 

    HEAD -> left = newNode ; 
}

void ThreadedBST::insert( int x ) {
    ThreadedNode* currentNode = HEAD -> left ; 
    ThreadedNode* parentNode = HEAD -> left ; 
    while( true ) {
        parentNode = currentNode ; 
        if( currentNode -> val > x ) {
            if( currentNode -> lbit == 1 ) {
                currentNode = currentNode -> left ; // Go left
            }
            else {
                break ; 
            }
        }
        else {
            if( currentNode -> rbit == 1 ) {
                currentNode = currentNode -> right ; // Go right
            }
            else {
                break ; 
            }
        }
    }
    cout << currentNode -> val << "\n" ; 
    cout << parentNode -> val << "\n" ;
    ThreadedNode* newNode = new( ThreadedNode ) ;
    newNode -> val = x ; 
    if( parentNode -> val < x ) {
        // x is greater than parent, insert right
        newNode -> right = parentNode -> right ; 
        newNode -> rbit = parentNode -> rbit ; 
        newNode -> lbit = 0 ; 
        newNode -> left = parentNode ; 
        parentNode -> rbit = 1 ; 
        parentNode -> right = newNode ; 
    }
    else {
        // x is smaller than parent, insert left
        newNode -> left = parentNode -> left ; 
        newNode -> lbit = parentNode -> lbit ; 
        newNode -> rbit = 0 ; 
        newNode -> right = parentNode ; 
        parentNode -> lbit = 1 ; 
        parentNode -> left = newNode ; 
    }
}

ThreadedNode* ThreadedBST::inorderSuccessor( ThreadedNode* node ) {
    ThreadedNode* succ = node -> right ; 
    if( node -> rbit == 1  ){
        // Node has right child, 
        // then go to leftmost child
        while( succ -> lbit == 1 ) {
            succ = succ -> left ; 
        }
    }
    return succ ; 
}

void ThreadedBST::inorder() {
    ThreadedNode* currentNode = HEAD ; 
    while( true ) {
        currentNode = inorderSuccessor( currentNode ) ;
        if( currentNode == HEAD ) {
            return ; 
        }
        cout << currentNode -> val << " " ; 
    }
}

void ThreadedBST::deleteChildNode( ThreadedNode* parentNode , ThreadedNode* childNode ) {
    // We need to delete child node
    // Check for three cases
    if( childNode -> lbit == 1 && childNode -> rbit == 1 ) {
        // Deletion of node with two children
    }
    else if( childNode -> lbit == 0 && childNode -> rbit == 0 ) {
        // Deletion of node with no children i.e. leaf node
    }
    else {
        // Deletion of node with one child
        if( childNode -> lbit == 1 && childNode -> rbit == 0 ) {
            // Left child is node
            // Right child is a thread
            if( parentNode -> left == childNode ) {

            }
            else if( parentNode -> right == childNode ) {

            }
            delete childNode ; 
        }
        else if( childNode -> lbit == 0 && childNode -> rbit == 1 ) {
            // Left child is thread
            // Right child is a node
            if( parentNode -> left == childNode ) {

            }
            else if( parentNode -> right == childNode ) {

            }
            delete childNode ; 
        }
    }
}

int main() {

    ThreadedBST tree ; 
    tree.create( 50 ) ; 
    tree.insert( 60 ) ; 
    tree.insert( 30 ) ;
    tree.insert( 10 ) ; 
    tree.insert( 20 ) ; 
    tree.insert( 40 ) ; 
    tree.insert( 80 ) ; 
    tree.insert( 75 ) ; 
    tree.inorder() ;
 
    return 0 ; 
}