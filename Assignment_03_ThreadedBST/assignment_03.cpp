#include <iostream>
using namespace std;

/*
Create an inordered threaded binary search tree. Perform inorder,
preorder traversals without recursion and deletion of a node. Analyze
time and space complexity of the algorithm.
*/

class ThreadedNode {
	int val ;
	ThreadedNode* left = nullptr ;
	ThreadedNode* right = nullptr ;
	bool rThread = false ;
	friend class ThreadedBinarySearchTree ;
};

class ThreadedBinarySearchTree {

	ThreadedNode* ROOT ;

public:

	void create( int rootValue ) ;
	void insert( int num ) ;
	void preorder() ;
	void inorder() ;
	void deleteNode() ;

};

void ThreadedBinarySearchTree::create( int rootValue ) {
	ROOT = new( ThreadedNode ) ;
	ROOT -> val = rootValue ;
}

void ThreadedBinarySearchTree::insert( int num ) {
	ThreadedNode* newNode = new( ThreadedNode ) ;
	newNode -> val = num ;
	ThreadedNode* currentNode = ROOT ;
	ThreadedNode* prevNode = nullptr ;
	while( currentNode != nullptr ) {
		prevNode = currentNode ;
		if( currentNode -> val > num ) {
			// Go left
			currentNode = currentNode -> left ;
		}
		else {
			// Go right if rThread is False
			// We wish to travel down the tree,
			// if we encounter a thread, break the loop (as we've encountered a leaf node)
			if( !(currentNode -> rThread) ) {
				currentNode = currentNode -> right ;
			}
			else {
				break;
			}
		}
	}
	if( num < prevNode -> val ) {
		// Add thread to parent node
		newNode -> right = prevNode ;
		newNode -> rThread = true ;
		// Set new node as left child
		prevNode -> left = newNode  ;
	}
	else {
		// Add thread of parent node to child node
		newNode -> right = prevNode -> right ;
		newNode -> rThread = prevNode -> rThread ;
		// Remove thread from parent node
		prevNode -> rThread = false ;
		// Set new node as right child
		prevNode -> right = newNode ;
	}
}

void ThreadedBinarySearchTree::inorder() {
	// Inorder: LEFT  - ROOT  - RIGHT
	ThreadedNode* currentNode = ROOT ;
	// Travel to leftmost child
	while( currentNode -> left != nullptr ) {
		currentNode = currentNode -> left ;
	}
	while( true ) {
		cout << currentNode -> val << " " ;
		if( currentNode -> right == nullptr && currentNode -> left == nullptr ) {
			// If both left and right child are null, there are no threads
			// and we've reached the rightmost element of the tree
			cout << "\n" ;
			return ;
		}
		if( currentNode -> rThread ) {
			// Thread is present, update currentNode to the node pointed by thread
			currentNode = currentNode -> right ;
		}
		else {
			// If there's no thread, go the right child
			// and from there proceed to the leftmost child (in that subtree)
			currentNode = currentNode -> right ;
			while( currentNode -> left != nullptr ) {
				currentNode = currentNode -> left ;
			}
		}
	}
}

void ThreadedBinarySearchTree::preorder() {
	// Inorder: ROOT  -  LEFT  - RIGHT
	ThreadedNode* currentNode = ROOT ;
	// Go the leftmost node of the tree and print the nodes
	while( currentNode -> left != nullptr ) {
		cout << currentNode -> val << " " ;
		currentNode = currentNode -> left ;
	}
	cout << currentNode -> val << " " ;
	while( true ) {
		if( currentNode -> right == nullptr && currentNode -> left == nullptr ) {
			cout << "\n" ;
			return ;
		}
		if( currentNode -> rThread ) {
			// If an rThread is present, go the node pointed by the thread
			// instead of printing this node (as in the case of inorder), we print
			// its right child (if it is not null)
			currentNode = currentNode -> right ;
			if( currentNode -> right != nullptr && !(currentNode -> rThread) ) {
				cout << currentNode -> right -> val << " " ; 
			}
		}
		else {
			// If there's no thread, go the right child
			// and from there proceed to the leftmost child (in that subtree)
			currentNode = currentNode -> right ;
			while( currentNode -> left != nullptr ) {
				currentNode = currentNode -> left ;
			}
		}
	}
}


int main() {

	ThreadedBinarySearchTree tree ;
	tree.create( 20 ) ;
	tree.insert( 15 ) ; 
	tree.insert( 17 ) ;
	tree.insert( 10 ) ;
	tree.insert( 5 ) ; 
	tree.insert( 30 ) ; 
	tree.inorder() ;
	tree.preorder() ; 


	return 0;
}
