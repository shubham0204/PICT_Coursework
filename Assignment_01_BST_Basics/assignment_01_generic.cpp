#include <iostream>
#include <stack>
#include <vector>
#include <map>
using namespace std;

/*
21356 - Shubham Panchal
Beginning with an empty binary search tree, Construct binary search tree by inserting
the values in the order given. After constructing a binary tree -
i. Insert new node, ii. Find number of nodes in longest path from root, iii. Minimum data
value found in the tree, iv. Change a tree so that the roles of the left and right pointers
are swapped at every node, v. Search a value
*/

template <class E>
class BinarySearchTree;

template <class E>
class Node
{
	E val;
	Node *left = nullptr;
	Node *right = nullptr;
	friend class BinarySearchTree<E>;
};

template <class E>
class BinarySearchTree
{

	Node<E> *ROOT;
	map<Node<E> *, int> nodeLevels;
	int numElements;

public:
	enum Traversals
	{
		PREORDER,
		INORDER,
		POSTORDER,
	};

	BinarySearchTree()
	{
		ROOT = nullptr;
		numElements = 0;
	}

	void create(E rootNodeValue)
	{
		ROOT = new (Node<E>);
		ROOT->val = rootNodeValue;
	}

	void insert(E element)
	{
		// Allocate new node
		Node<E> *newNode = new (Node<E>);
		newNode->val = element;

		Node<E> *currentNode = ROOT; // Start with ROOT node
		Node<E> *prevNode = nullptr; // Node travelled before currentNode

		while (currentNode != nullptr)
		{
			prevNode = currentNode;
			if (element < currentNode->val)
			{
				currentNode = currentNode->left; // Go Right
			}
			else
			{
				currentNode = currentNode->right; // Go Left
			}
		}
		if (element < prevNode->val)
		{
			prevNode->left = newNode; // Smaller value, create left child
		}
		else
		{
			prevNode->right = newNode; // Greater element, create right child
		}
		numElements++;
	}

	Node<E> *getRoot()
	{
		return ROOT;
	}

	void recursiveTraversal(Traversals traversal)
	{
		switch (traversal)
		{
		case INORDER:
			displayInOrderRecursive(ROOT);
			break;
		case PREORDER:
			displayPreOrderRecursive(ROOT);
			break;
		case POSTORDER:
			displayPostOrderRecursive(ROOT);
			break;
		}
	}

	void displayInOrderRecursive(Node<E> *currentNode)
	{
		if (currentNode == nullptr)
		{
			return;
		}
		displayInOrderRecursive(currentNode->left);
		cout << currentNode->val << " ";
		displayInOrderRecursive(currentNode->right);
	}

	void displayPreOrderRecursive(Node<E> *currentNode)
	{
		if (currentNode == nullptr)
		{
			return;
		}
		cout << currentNode->val << " ";
		displayPreOrderRecursive(currentNode->left);
		displayPreOrderRecursive(currentNode->right);
	}

	void displayPostOrderRecursive(Node<E> *currentNode)
	{
		if (currentNode == nullptr)
		{
			return;
		}
		displayPostOrderRecursive(currentNode->left);
		displayPostOrderRecursive(currentNode->right);
		cout << currentNode->val << " ";
	}

	void displayPreOrder()
	{
		stack<Node<E> *> s;
		Node<E> *currentNode = ROOT;
		while (currentNode != nullptr || !s.empty())
		{
			if (currentNode != nullptr)
			{
				cout << currentNode->val << " ";
				s.push(currentNode);
				currentNode = currentNode->left;
			}
			else
			{
				currentNode = s.top()->right;
				s.pop();
			}
		}
	}

	void longestLength()
	{
		stack<Node<E> *> s;
		Node<E> *currentNode = ROOT;
		int currentLevel = 0;
		while (currentNode != nullptr || !s.empty())
		{
			if (currentNode != nullptr)
			{
				// Keep travelling leftwards and stack all nodes travelled
				// Also, increase the level by 1
				s.push(currentNode);
				nodeLevels[currentNode] = currentLevel++;
				currentNode = currentNode->left;
			}
			else
			{
				// Check if parent node on the node has a right child
				// If the node does not have a right child, pop and check next node
				// in the stack
				currentNode = s.top()->right;
				s.pop();
				if (currentNode != nullptr)
				{
					// The parent node had a right child,
					// decrement the level by 1
					currentLevel--;
				}
			}
		}
		for (typename map<Node<E> *, int>::iterator itr = nodeLevels.begin(); itr != nodeLevels.end(); itr++)
		{
			cout << "Node: " << itr->first->val << " Length: " << itr->second << "\n";
		}
	}

	E getMinElement()
	{
		// Travel to the leftmost node
		Node<E> *currentNode = ROOT;
		while (currentNode->left != nullptr)
		{
			currentNode = currentNode->left;
		}
		return currentNode->val;
	}

	E getMaxElement()
	{
		// Travel to the rightmost node
		Node<E> *currentNode = ROOT;
		while (currentNode->right != nullptr)
		{
			currentNode = currentNode->right;
		}
		return currentNode->val;
	}

	void mirror()
	{
		swapLeftRightChildren(ROOT);
	}

	void swapLeftRightChildren(Node<E> *currentNode)
	{
		if (currentNode == nullptr)
		{
			// Leaf node reached, end recursive calls
			return;
		}
		// Swap left and right nodes
		Node<E> *leftNode = currentNode->left;
		currentNode->left = currentNode->right;
		currentNode->right = leftNode;
		// Proceed to left and right subtrees
		swapLeftRightChildren(currentNode->left);
		swapLeftRightChildren(currentNode->right);
	}

	bool search(E key)
	{
		Node<E> *currentNode = ROOT;
		bool found = false;
		while (currentNode != nullptr)
		{
			if (key < currentNode->val)
			{
				currentNode = currentNode->left;
			}
			else if (key > currentNode->val)
			{
				currentNode = currentNode->right;
			}
			else
			{
				found = true;
				break;
			}
		}
		return found;
	}
};

int main()
{
	BinarySearchTree<int> tree;
	tree.create(5);
	tree.insert(10);
	tree.insert(25);
	tree.insert(17);
	tree.insert(8);
	tree.insert(3);

	cout << "Preorder (Recursive): ";
	tree.recursiveTraversal(tree.PREORDER);
	cout << "\n";

	cout << "Inorder (Recursive): ";
	tree.recursiveTraversal(tree.INORDER);
	cout << "\n";

	cout << "Postorder (Recursive): ";
	tree.recursiveTraversal(tree.POSTORDER);
	cout << "\n";

	int min = tree.getMinElement();
	int max = tree.getMaxElement();
	cout << "max element: " << max << "\n";
	cout << "min element: " << min << "\n";

	cout << "Node path lengths: "
		 << "\n";
	tree.longestLength();

	int key;
	cout << "Enter key to search in BST: "
		 << "\n";
	cin >> key;
	if (tree.search(key))
	{
		cout << "Element found in tree"
			 << "\n";
	}
	else
	{
		cout << "Element not found in tree"
			 << "\n";
	}

	cout << "Mirrored tree preorder: ";
	tree.mirror();
	tree.displayPreOrder();
	cout << "\n";

	return 0;
}
