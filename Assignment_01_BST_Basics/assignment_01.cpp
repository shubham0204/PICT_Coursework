#include <iostream>
using namespace std;

/*
21356 - Shubham Panchal
Beginning with an empty binary search tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree -
i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data
value found in the tree, iv. Change a tree so that the roles of the left and right pointers
are swapped at every node, v. Search a value
*/
class Node {
	int val ;
	Node* left = nullptr ;
	Node* right = nullptr ;
	friend class BinarySearchTree ;
};

class BinarySearchTree {

public:

	Node* ROOT ;

	BinarySearchTree() {
		ROOT = nullptr ;
	}

	void create( int root ) {
		ROOT = new( Node ) ;
		ROOT -> val = root ;
	}

	void insert( int element ) {
		// Allocate new node
		Node* newNode = new( Node ) ;
		newNode -> val = element ;

		// Start with ROOT node
		Node* currentNode = ROOT ;
		// Node travelled before currentNode
		Node* prevNode = nullptr ;

		while( currentNode != nullptr ) {
			prevNode = currentNode ;
			if( element < currentNode -> val ) {
				// Go Left
				currentNode = currentNode -> left ;
			}
			else {
				// Go Right
				currentNode = currentNode -> right ;
			}
		}
		if( element < prevNode -> val ) {
			// Smaller element, create left child
			prevNode -> left = newNode ;
		}
		else {
			// Greater element, create right child
			prevNode -> right = newNode ;
		}
	}

	void displayInOrder( Node* currentNode ) {
		if( currentNode == nullptr ) {
			return;
		}
		displayInOrder( currentNode -> left ) ;
		cout << currentNode -> val << " " ;
		displayInOrder( currentNode -> right ) ;
	}

	void displayPreOrder( Node* currentNode ) {
		if( currentNode == nullptr ) {
			return;
		}
		cout << currentNode -> val << " " ;
		displayPreOrder( currentNode -> left ) ;
		displayPreOrder( currentNode -> right ) ;
	}

	void displayPostOrder( Node* currentNode ) {
		if( currentNode == nullptr ) {
			return;
		}
		displayPostOrder( currentNode -> left ) ;
		displayPostOrder( currentNode -> right ) ;
		cout << currentNode -> val << " " ;
	}

};

int main() {
	BinarySearchTree tree ;
	tree.create( 5 ) ;
	tree.insert( 10 ) ;
	tree.insert( 25 ) ;
	tree.insert( 17 ) ;
	tree.insert( 8 ) ;
	tree.insert( 3 ) ;
	tree.displayInOrder( tree.ROOT ) ;
	cout << "\n" ;
	tree.displayPostOrder( tree.ROOT ) ;
	cout << "\n" ;
	tree.displayPreOrder( tree.ROOT ) ;

	return 0;
}
