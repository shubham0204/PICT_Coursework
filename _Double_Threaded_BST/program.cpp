#include <iostream>
using namespace std;

class Node {

	int val ;
	Node* left = nullptr ;
	Node* right = nullptr ;
	int lbit = 0 ;
	int rbit = 0 ;

public:

	friend class ThreadedBST ;

};

class ThreadedBST {

	Node* HEAD = nullptr ;
	Node* ROOT = nullptr ;

public:

	void create( int rootVal ) {

		ROOT = new( Node ) ;
		ROOT -> val = rootVal ;

		HEAD = new( Node ) ;
		HEAD -> val = -1 ;
		HEAD -> right = HEAD ;
		HEAD -> rbit = 1 ;
		HEAD -> left = ROOT ;
		HEAD -> lbit = 1 ;

		ROOT -> lbit = 0 ;
		ROOT -> left = HEAD ;
		ROOT -> rbit = 0 ;
		ROOT -> right = HEAD ;

	}

	void insert( int nodeVal ) {
		Node* currentNode = HEAD -> left ;
		Node* parentNode = HEAD -> left ;
		while( true ) {
			parentNode = currentNode ;
			if( currentNode -> val > nodeVal ) {
				if( currentNode -> lbit == 1 ) {
					currentNode = currentNode -> left ;
				}
				else {
					break ;
				}
			}
			else {
				if( currentNode -> rbit == 1 ) {
					currentNode = currentNode -> right ;
				}
				else {
					break ;
				}
			}
		}

		Node* newNode = new( Node ) ;
		newNode -> val = nodeVal ;
		if( parentNode -> val > nodeVal ) {
			newNode -> left = parentNode -> left ;
			newNode -> lbit = parentNode -> lbit ;

			newNode -> rbit = 0 ;
			newNode -> right = parentNode ;

			parentNode -> lbit = 1 ;
			parentNode -> left = newNode ;
		}
		else {
			newNode -> right = parentNode -> right ;
			newNode -> rbit = parentNode -> rbit ;

			newNode -> lbit = 0 ;
			newNode -> left = parentNode ;

			parentNode -> rbit = 1 ;
			parentNode -> right = newNode ;
		}
	}

	Node* inorderSuccessor( Node* node ) {
		Node* curr = node -> right ;
		if( node -> rbit == 1 ) {
			while( curr -> lbit != 0 ) {
				curr = curr -> left ;
			}
		}
		return curr ;
	}

	void inorder() {
		Node* curr = HEAD ;
		while( true ) {
			curr = inorderSuccessor( curr ) ;
			if( curr == HEAD ) {
				cout << "\n" ;
				return ;
			}
			cout << curr -> val << " " ;
		}
	}

	void preorder() {
		int flag = 1 ;
		Node* curr = HEAD -> left ;
		while( curr != HEAD ) {
			while( flag != 0 ) {
				cout << curr -> val << " " ;
				if( curr -> lbit == 1 ) {
					curr = curr -> left ;
				}
				else {
					break ;
				}
			}
			flag = curr -> rbit ;
			curr = curr -> right ;
		}
		cout << "\n" ;
	}

	void del( int val ) {
		Node* currentNode = HEAD -> left ;
		Node* parentNode = HEAD ;
		while( currentNode -> val != val ) {
			parentNode = currentNode ;
			if( val > currentNode -> val ) {
				if( currentNode -> rbit == 1 ) {
					currentNode = currentNode -> right ;
				}
				else { break; }
			}
			else {
				if( currentNode -> lbit == 1 ) {
					currentNode = currentNode -> left ;
				}
				else {
					break;
				}
			}
		}
		delNode( parentNode , currentNode ) ;
	}

	void delNode( Node* parent , Node* currNode ) {

		if( currNode -> lbit == 1 && currNode -> rbit == 1 ) {
			// Two child node
			Node* leftmost = currNode -> right ;
			parent = currNode ;
			while( leftmost -> lbit == 1 ) {
				parent = leftmost ;
				leftmost = leftmost -> left ;
			}
			int temp = currNode -> val ;
			currNode -> val = leftmost -> val ;
			leftmost -> val = temp ;
			currNode = leftmost ;
		}

		if( currNode -> lbit == 0 && currNode -> rbit == 0 ) {
			// Leaf node deletion
			if( parent -> left == currNode ) {
				parent -> left = currNode -> left ;
				parent -> lbit = currNode -> lbit ;
			}
			else if( parent -> right == currNode ) {
				parent -> right = currNode -> right ;
				parent -> rbit = currNode -> rbit ;
			}
			delete currNode ;
		}
		else {
			if( currNode -> lbit == 1 && currNode -> rbit == 0 ) {
				parent -> left = currNode -> left ;
				currNode -> left -> right = parent ;
			}
			else if( currNode -> lbit == 0 && currNode -> rbit == 1 ) {
				parent -> right = currNode -> right ;
				currNode -> right -> left = parent ;
			}
			delete currNode ;
		}

	}

};

int main() {

	ThreadedBST tree;
	tree.create( 50 ) ;
	tree.inorder() ;
	tree.preorder() ;

	tree.del( 50 ) ;
	tree.inorder() ;


	return 0;
}
