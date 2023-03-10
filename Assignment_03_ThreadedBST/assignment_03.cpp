#include <iostream>
using namespace std;

/*
Create an inordered threaded binary search tree. Perform inorder,
preorder traversals without recursion and deletion of a node. Analyze
time and space complexity of the algorithm.
*/

class ThreadedNode
{
	int val;
	ThreadedNode *left = nullptr;
	ThreadedNode *right = nullptr;
	bool rThread = false;
	friend class ThreadedBinarySearchTree;
};

class ThreadedBinarySearchTree
{

	ThreadedNode *ROOT;

public:
	void create(int rootValue);
	void insert(int num);
	void preorder();
	void inorder();
	void deleteNode(int num);
};

void ThreadedBinarySearchTree::create(int rootValue)
{
	ROOT = new (ThreadedNode);
	ROOT->val = rootValue;
}

void ThreadedBinarySearchTree::insert(int num)
{
	ThreadedNode *newNode = new (ThreadedNode);
	newNode->val = num;
	ThreadedNode *currentNode = ROOT;
	ThreadedNode *prevNode = nullptr;
	while (currentNode != nullptr)
	{
		prevNode = currentNode;
		if (currentNode->val > num)
		{
			// Go left
			currentNode = currentNode->left;
		}
		else
		{
			// Go right if rThread is False
			// We wish to travel down the tree,
			// if we encounter a thread, break the loop (as we've encountered a leaf node)
			if (!(currentNode->rThread))
			{
				currentNode = currentNode->right;
			}
			else
			{
				break;
			}
		}
	}
	if (num < prevNode->val)
	{
		// Add thread to parent node
		newNode->right = prevNode;
		newNode->rThread = true;
		// Set new node as left child
		prevNode->left = newNode;
	}
	else
	{
		// Add thread of parent node to child node
		newNode->right = prevNode->right;
		newNode->rThread = prevNode->rThread;
		// Remove thread from parent node
		prevNode->rThread = false;
		// Set new node as right child
		prevNode->right = newNode;
	}
}

void ThreadedBinarySearchTree::inorder()
{
	// Inorder: LEFT  - ROOT  - RIGHT
	ThreadedNode *currentNode = ROOT;
	// Travel to leftmost child
	while (currentNode->left != nullptr)
	{
		currentNode = currentNode->left;
	}
	while (true)
	{
		cout << currentNode->val << " ";
		if (currentNode->right == nullptr && currentNode->left == nullptr)
		{
			// If both left and right child are null, there are no threads
			// and we've reached the rightmost element of the tree
			cout << "\n";
			return;
		}
		if (currentNode->rThread)
		{
			// Thread is present, update currentNode to the node pointed by thread
			currentNode = currentNode->right;
		}
		else if(currentNode -> right == nullptr){
			cout << "\n" ; 
            return;
        }
		else
		{
			// If there's no thread, go the right child
			// and from there proceed to the leftmost child (in that subtree)
			if (currentNode->right != nullptr)
			{
				currentNode = currentNode->right;
				while (currentNode->left != nullptr)
				{
					currentNode = currentNode->left;
				}
			}
			else
			{
				cout << "\n";
				return;
			}
		}
	}
}

void ThreadedBinarySearchTree::preorder() {
	ThreadedNode* currentNode = ROOT ;
	cout << currentNode -> val << " " ; 
	while( true ) {
		while( currentNode -> left != nullptr ) {
			currentNode = currentNode -> left ; 
			cout << currentNode -> val << " " ; 
		}
		while( currentNode -> rThread ) {
			currentNode = currentNode -> right ; 
		}
		currentNode = currentNode -> right ; 
		if( currentNode != nullptr ) {
			cout << currentNode -> val << " " ; 
		}
		else {
			cout << "\n" ; 
			return ;
		}
	} 
}

void ThreadedBinarySearchTree::deleteNode( int num ) {
	ThreadedNode *currentNode = ROOT;
	ThreadedNode *prevNode = nullptr;
	while (currentNode -> right != nullptr && currentNode -> left != nullptr ){
		prevNode = currentNode;
		if (currentNode->val > num) {
			// Go left
			currentNode = currentNode->left;
		}
		else {
			// Go right if rThread is False
			// We wish to travel down the tree,
			// if we encounter a thread, break the loop (as we've encountered a leaf node)
			if (!(currentNode->rThread)) {
				currentNode = currentNode->right;
			}
			else {
				break;
			}
		}
	}

	if( currentNode -> left == nullptr && currentNode -> right == nullptr ) {
		// Leaf node deletion
		if( prevNode -> left == currentNode ) {
			prevNode -> left = nullptr ;
		}
		else if( prevNode -> right == currentNode ) {
			prevNode -> right = nullptr ;
		}
		delete currentNode ;
	}
	else if( currentNode -> left != nullptr && currentNode -> right != nullptr ) {
		// currentNode has two children
		ThreadedNode* minInRightTree = currentNode -> right ; 
		ThreadedNode* newParent = currentNode ; 
		while( minInRightTree -> left != nullptr ) {
			newParent = minInRightTree ;
			minInRightTree = minInRightTree -> left ; 
		}
		currentNode -> val = minInRightTree -> val ; 
		newParent -> left = minInRightTree -> right ; 
		newParent -> rThread = minInRightTree -> rThread ; 
		delete minInRightTree ; 
	}
	else {
		if( currentNode -> left != nullptr ) {
			prevNode -> left = currentNode -> left ; 
			delete currentNode ; 
		}
		else if( currentNode -> right != nullptr ) {
			prevNode -> right = currentNode -> right ; 
			prevNode -> rThread = currentNode -> rThread ; 

			delete currentNode ; 
		}
	}

}

int main()
{

	ThreadedBinarySearchTree tree;
	tree.create(20);
	tree.insert(15);
	tree.insert(17);
	tree.insert(10);
	tree.insert(5);
	tree.insert(30);
	tree.insert(25);
	tree.insert(12);
	tree.insert(60);
	tree.inorder();
	tree.preorder() ; 
	tree.deleteNode( 25 ) ; 

	tree.inorder() ; 

	return 0;
}
