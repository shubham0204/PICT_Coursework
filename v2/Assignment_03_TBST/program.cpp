#include <iostream>
using namespace std;

class Node {

    int val ; 
    Node* left = nullptr ; 
    Node* right = nullptr ; 
    int rbit = 0 ; 
    int lbit = 0 ;

    public:

    friend class ThreadedBST ; 

} ; 

class ThreadedBST {

    Node* HEAD = nullptr ; 
    Node* ROOT = nullptr ; 

    public:

    void create( int rootVal ) {
        ROOT = new( Node ) ;
        ROOT -> val = rootVal ; 

        HEAD = new( Node ) ; 
        HEAD -> val = 0 ; 
        HEAD -> rbit = 1 ; 
        HEAD -> right = HEAD ; 
        HEAD -> lbit = 1 ; 
        HEAD -> left = ROOT ; 

        ROOT -> lbit = 0 ; 
        ROOT -> left = HEAD ; 
        ROOT -> rbit = 0 ; 
        ROOT -> right = HEAD ; 
    }

    void insert( int key ) {
        Node* curr = ROOT ; 
        Node* parent = nullptr ;

        while( curr != nullptr ) {
            parent = curr ; 
            if( curr -> val > key ) {
                if( curr -> lbit == 1 ) {
                    curr = curr -> left ; 
                }
                else {
                    break ; 
                }
            }
            else {
                if( curr -> rbit == 1 ) {
                    curr = curr -> right ; 
                }
                else {
                    break ; 
                }
            }
        }

        Node* newNode = new( Node ) ; 
        newNode -> val = key ; 

        if( parent -> val < key ) {
            // Insert right 
            newNode -> rbit = parent -> rbit ; 
            newNode -> right = parent -> right ; 

            newNode -> lbit = 0 ; 
            newNode -> left = parent ; 

            parent -> rbit = 1 ; 
            parent -> right = newNode ; 
        }
        else {
            // Insert left
            newNode -> lbit = parent -> lbit ; 
            newNode -> left = parent -> left ; 

            newNode -> rbit = 0 ; 
            newNode -> right = parent ; 

            parent -> lbit = 1 ; 
            parent -> left = newNode ;
        }

    }

    Node* inorderSuccessor( Node* node ) {
        Node* succ = node -> right ; 
        if( node -> rbit == 1 ) {
            while( succ -> lbit == 1 ) {
                succ = succ -> left ; 
            }
        }
        return succ ; 
    }

    void inorder() {
        Node* curr = HEAD ; 
        while( true ) {
            curr = inorderSuccessor( curr ) ; 
            if( curr == HEAD ) {
                cout << "\n" ; 
                break ; 
            }
            cout << curr -> val << " " ; 
        }
    }

    void deleteNode( int key ) {
        Node* curr = HEAD -> left ; 
        Node* parent = HEAD -> left ;
        while( curr -> val != key ) {
            parent = curr ; 
            if( key > curr -> val ) {
                if( curr -> rbit == 1 ) {
                    curr = curr -> right ; 
                }
            }
            else if ( key < curr -> val ) {
                if( curr -> lbit == 1 ) {
                    curr = curr -> left ; 
                }
            }
        }
        deleteChildParent( curr , parent ) ; 
    }

    void deleteChildParent( Node* child , Node* parent ) {

        if( child -> lbit == 1 && child -> rbit == 1 ) {
            Node* node = child -> right ;
            while( node -> lbit != 0 ) { 
                node = node -> left ; 
            }
            child -> val = node -> val ;
            child = node ;  
        }

        if( child -> rbit == 0 && child -> lbit == 0 ) {
            if( parent -> left == child ) {
                parent -> lbit = child -> lbit ; 
                parent -> left = child -> left ; 
            }
            else if( parent -> right == child ) {
                parent -> rbit = child -> rbit ; 
                parent -> right =  child -> right ;
            }
        }
        else {
            if( child -> lbit == 0 && child -> rbit == 1 ) {
                // Left thread, right child
                if( parent -> right == child ) {
                    parent = child -> right ; 
                }
                else if( parent -> left == child ) {
                    parent = child -> left ; 
                }
                while( parent -> rbit != 1 ) {
                    parent = parent -> right ; 
                }
                parent -> right = child -> right ; 
                delete child ; 
            }
            else if( child -> lbit == 1 && child -> rbit == 0 ) {
                // Left thread, right child
                if( parent -> right == child ) {
                    parent = child -> right ; 
                }
                else if( parent -> left == child ) {
                    parent = child -> left ; 
                }
                while( parent -> lbit != 1 ) {
                    parent = parent -> left ; 
                }
                parent -> left = child -> left ; 
                delete child ; 
            }
        }

    }

} ; 


int main() {

    ThreadedBST tree;
    tree.create(50);
    tree.insert(60);
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);
    tree.insert(40);
    tree.insert(80);
    tree.insert(75);
    tree.inorder();
    // tree.preorder();

    tree.deleteNode(20);
    tree.inorder();
    tree.deleteNode(40);
    tree.inorder();
    tree.deleteNode(75);
    tree.inorder();
    tree.deleteNode(80);
    tree.inorder();
    tree.deleteNode(60);
    tree.inorder();
    tree.deleteNode(30);
    tree.inorder();

    return 0;
}