#include <iostream>
#include <cmath>
using namespace std;

struct TreeNode {
    int val ; 
    TreeNode* left = nullptr ; 
    TreeNode* right = nullptr ; 
} ; 


class BinarySearchTree {

private:
TreeNode* ROOT = nullptr ; 

public:


// Operation 1
void createTree( int rootNodeVal ) {
    TreeNode* newNode = new TreeNode() ; 
    newNode -> val = rootNodeVal ;
    ROOT = newNode ; 
}


// Operation 2
void insert( int x ) {
    TreeNode* curr = ROOT ; 
    TreeNode* parent = ROOT ; 
    while( curr != nullptr ) {
        parent = curr ; 
        if( x > curr -> val ) {
            curr = curr -> right ; 
        }
        else {
            curr = curr -> left ; 
        }
    }
    TreeNode* newNode = new TreeNode() ; 
    newNode -> val = x ; 
    if( x < parent -> val ) {
        parent -> left = newNode ; 
    }
    else {
        parent -> right = newNode ; 
    }
}


// Operation 3
void travel() {
    inorder( ROOT ) ; 
    cout << "\n" ; 
}
void inorder( TreeNode* curr ) {
    if( curr == nullptr ) {
        return ; 
    }
    inorder( curr -> left ) ; 
    cout << curr -> val << " " ; 
    inorder( curr -> right ) ;
}


// Operation 4
TreeNode* search( int key ) {
    TreeNode* curr = ROOT ; 
    while( curr != nullptr ) {
        if( key < curr -> val ) {
            curr = curr -> left ; 
        }
        else if( key > curr -> val ) {
            curr = curr -> right ; 
        }
        else {
            cout << "Key Found!" << "\n" ; 
            return curr ; 
        }
    }
    cout << "Key Not Found" << "\n" ; 
    return nullptr ; 
}


// Operation 5
int minValue() {
    TreeNode* curr = ROOT ; 
    while( curr -> left != nullptr ) {
        curr = curr -> left ; 
    }
    return curr -> val ; 
}
int maxValue() {
    TreeNode* curr = ROOT ; 
    while( curr -> right != nullptr ) {
        curr = curr -> right ; 
    }
    return curr -> val ; 
}


// Operation 6
void mirror() {
    mirrorRecursive( ROOT ) ; 
}
void mirrorRecursive( TreeNode* curr ) {
    if( curr == nullptr ) {
        return ; 
    }
    TreeNode* temp = curr -> left ; 
    curr -> left = curr -> right ; 
    curr -> right = temp ; 
    mirrorRecursive( curr -> left ) ;
    mirrorRecursive( curr -> right ) ; 
}


// Operation 7
int longestPathLength() {
    return longestSubtreeHeight( ROOT ) ;
}
int longestSubtreeHeight( TreeNode* curr ) {
    if( curr == nullptr ) {
        return 0 ;
    }
    int leftSubTreeHeight = longestSubtreeHeight( curr -> left ) ; 
    int rightSubTreeHeight = longestSubtreeHeight( curr -> right ) ;
    return 1 + max( leftSubTreeHeight , rightSubTreeHeight ) ; 
}

} ; 

int main() {
    BinarySearchTree tree ; 
    tree.createTree( 50 ) ; 
    tree.insert( 25 ) ; 
    tree.insert( 60 ) ;  
    tree.insert( 70 ) ; 
    tree.insert( 80 ) ; 
    tree.insert( 90 ) ; 
    tree.travel() ; 

    tree.search( 50 ) ; 
    tree.search( 45 ) ; 

    cout << "Min Value is " << tree.minValue() << "\n" ; 
    cout << "Max Value is " << tree.maxValue() << "\n" ; 

    cout << "Longest Path length " << tree.longestPathLength() << "\n" ;

    tree.mirror() ; 
    tree.travel() ; 

    return 0;
}