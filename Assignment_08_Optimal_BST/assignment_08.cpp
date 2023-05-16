#include <iostream>
#include <vector>
#include "linkedqueue.cpp"
using namespace std;

struct Key {
	int value = 0 ;
	int freq = 0 ;
};

struct Node {
	int val ;
	Node* left = nullptr ;
	Node* right = nullptr ;
};

class OptimalBinarySearchTree {

private:

	Node* ROOT = nullptr ;
	vector<Key> keys ;

	void sortKeys() {
		for( int i = 0 ; i < keys.size() - 1 ; i++ ) {
			for( int j = 0 ; j < keys.size() - i - 1 ; j++ ) {
				if( keys[j].freq < keys[j+1].freq ) {
					Key temp = keys[j] ;
					keys[j] = keys[j+1] ;
					keys[j+1] = temp ;
				}
			}
		}
	}

	int insertInBST( int value ) {
		Node* newNode = new( Node ) ;
		newNode -> val = value ;
		int level = 1 ;
		if( ROOT == nullptr ) {
			ROOT = newNode ;
		}
		else {
			Node* currentNode = ROOT ;
			Node* prevNode = nullptr ;
			while( currentNode != nullptr ) {
				prevNode = currentNode ;
				if( currentNode -> val < value ) {
					currentNode = currentNode -> right ;
				}
				else {
					currentNode = currentNode -> left ;
				}
				level++ ;
			}

			if( value > prevNode -> val ) {
				prevNode -> right = newNode ;
			}
			else {
				prevNode -> left = newNode ;
			}
		}
		return level ;
	}


public:

	OptimalBinarySearchTree() {

	}

	void insertKey( int value , int freq ) {
		Key key ;
		key.value = value  ;
		key.freq = freq ;
		keys.push_back( key ) ;
	}

	void printKeys() {
		cout.width( 5 ) ;
		cout << "k_i" ;
		cout.width( 5 ) ;
		cout << "f_i" << "\n" ;
		for( Key k : keys ) {
			cout.width( 5 ) ;
			cout << k.value ;
			cout.width( 5 ) ;
			cout << k.freq << "\n";
		}
	}

	void createTree() {
		sortKeys() ;
		int cost = 0 ;
		for( Key key : keys ) {
			int numLevels = insertInBST( key.value ) ;
			cost += numLevels * key.freq ;
		}
		cout << "Cost: " << cost << "\n" ;
	}

	void BFS() {
		LinkedQueue<Node*> queue ;
		queue.push( ROOT ) ;
		while( !queue.isEmpty() ) {
			Node* poppedNode = queue.front() ;
			cout << poppedNode -> val << " " ;
			queue.pop() ;
			if( poppedNode -> right != nullptr ) {
				queue.push( poppedNode -> right ) ;
			}
			if( poppedNode -> left != nullptr ) {
				queue.push( poppedNode -> left ) ;
			}
		}
		cout << "\n" ;
 	}

};

int main() {

	OptimalBinarySearchTree tree;
	tree.insertKey( 10 , 2 ) ;
	tree.insertKey( 20 , 4 ) ;
	tree.insertKey( 30 , 3 ) ;
	tree.printKeys() ;

	tree.createTree() ;
	tree.BFS() ;


	return 0;
}
