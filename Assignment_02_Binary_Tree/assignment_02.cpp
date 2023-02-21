#include <iostream>
#include "linkedqueue.cpp"
#include "linkedstack.cpp"
using namespace std ; 

template <class E>
class BinaryTree ; 

template <class E>
class TreeNode {
    E val ; 
    TreeNode* left = nullptr ; 
    TreeNode* right = nullptr ; 
    friend class BinaryTree<E> ;
} ; 

template <class E>
class BinaryTree {

    TreeNode<E>* ROOT ; 
    LinkedQueue<TreeNode<E>*> nodes ; 

    public:

    enum Traversals {
        INORDER ,
        PREORDER , 
        POSTORDER
    } ; 

    void create( E rootNodeValue ) {
        ROOT = new( TreeNode<E> ) ;
        ROOT -> val = rootNodeValue ;
        insertNodeRecursive( ROOT ) ; 
    }
  
    void insertNodeRecursive( TreeNode<E>* parentNode ) {
        char option ; 
        cout << "Insert left node to " << parentNode -> val << "? " << "\n" ; cin >> option ; 
        if( option == 'y' ) {
            E newVal ; 
            cout << "Enter value for left node: " << "\n" ; cin >> newVal ; 
            TreeNode<E>* leftNode = new( TreeNode<E> ) ; 
            leftNode -> val = newVal ; 
            parentNode -> left = leftNode ; 
            nodes.push( leftNode ) ; 
        }
        cout << "Insert right node to " << parentNode -> val << "? " << "\n" ; cin >> option ; 
        if( option == 'y' ) {
            E newVal ; 
            cout << "Enter value for right node: " << "\n" ; cin >> newVal ; 
            TreeNode<E>* rightNode = new( TreeNode<E> ) ; 
            rightNode -> val = newVal ; 
            parentNode -> right = rightNode ; 
            nodes.push( rightNode ) ; 
        }
        if( !nodes.isEmpty() ) {
            insertNodeRecursive( nodes.pop() ) ;
        }
    }

    void recursiveTraversal( Traversals traversal ) {
		switch( traversal ) {
			case INORDER: 
			    displayInOrderRecursive( ROOT ) ; 
				break ; 
			case PREORDER: 
			    displayPreOrderRecursive( ROOT ) ; 
				break ; 
			case POSTORDER:
			    displayPostOrderRecursive( ROOT ) ; 
				break ; 
		}
	}

	void displayInOrderRecursive( TreeNode<E>* currentNode ) {
		if( currentNode == nullptr ) {
			return;
		}
		displayInOrderRecursive( currentNode -> left ) ;
		cout << currentNode -> val << " " ;
		displayInOrderRecursive( currentNode -> right ) ;
	}

	void displayPreOrderRecursive( TreeNode<E>* currentNode ) {
		if( currentNode == nullptr ) {
			return;
		}
		cout << currentNode -> val << " " ;
		displayPreOrderRecursive( currentNode -> left ) ;
		displayPreOrderRecursive( currentNode -> right ) ;
	}

	void displayPostOrderRecursive( TreeNode<E>* currentNode ) {
		if( currentNode == nullptr ) {
			return;
		}
		displayPostOrderRecursive( currentNode -> left ) ;
		displayPostOrderRecursive( currentNode -> right ) ;
		cout << currentNode -> val << " " ;
	}

    void mirror() {
		swapLeftRightChildren( ROOT ) ;  
	}

    void mirrorIterative() {

    }

	void swapLeftRightChildren( TreeNode<E>* currentNode ) {
		if( currentNode == nullptr ) {
			// Leaf node reached, end recursive calls
			return ; 
		}
		// Swap left and right nodes
		TreeNode<E>* leftNode = currentNode -> left ; 
		currentNode -> left = currentNode -> right ; 
		currentNode -> right = leftNode ; 
		// Proceed to left and right subtrees
		swapLeftRightChildren( currentNode -> left ) ; 
		swapLeftRightChildren( currentNode -> right ) ; 
	}


} ; 

int main() {
    BinaryTree<int> tree;
	// tree.create( 34 ) ;
    // tree.recursiveTraversal( tree.INORDER ) ; 

	Stack<int> stack ;
	stack.push( 34 ) ;
	stack.push( 53 ) ;
	stack.push( 12 ) ;
	stack.print() ; 
	stack.pop() ; 
	stack.print() ; 

    return 0 ; 
}