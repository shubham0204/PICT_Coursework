#include <iostream>
using namespace std;

class ThreadedNode
{
    int val;
    ThreadedNode *left = nullptr;
    ThreadedNode *right = nullptr;
    int lbit = 0; // 0 -> Thread, 1 -> Child
    int rbit = 0; // 0 -> Thread, 1 -> Child
    friend class ThreadedBST;
};

class ThreadedBST
{

    ThreadedNode *HEAD;
    ThreadedNode *ROOT;

public:
    void create(int rootValue);
    void insert(int value);

    ThreadedNode *inorderSuccessor(ThreadedNode *node);
    void inorder();

    void preorder();

    void deleteChildNode(ThreadedNode *parentNode, ThreadedNode *childNode);
    void deleteNode(int x);
};

void ThreadedBST::create(int rootValue)
{
    ThreadedNode *newNode = new (ThreadedNode);
    newNode->val = rootValue;

    HEAD = new (ThreadedNode);
    HEAD->val = 0;
    HEAD->rbit = 1;
    HEAD->lbit = 1;
    HEAD->right = HEAD;

    newNode->rbit = 0; // thread
    newNode->lbit = 0;
    newNode->right = HEAD;
    newNode->left = HEAD;

    HEAD->left = newNode;
}

void ThreadedBST::insert(int x)
{
    ThreadedNode *currentNode = HEAD->left; // ROOT
    ThreadedNode *parentNode = HEAD->left;  // ROOT
    while (true)
    {
        parentNode = currentNode;
        if (currentNode->val > x)
        { // ;left
            if (currentNode->lbit == 1)
            {
                // left -> child
                currentNode = currentNode->left; // Go left
            }
            else
            {
                break;
            }
        }
        else
        { // x > currentNode -> val
            if (currentNode->rbit == 1)
            {                                     // right
                currentNode = currentNode->right; // Go right
            }
            else
            {
                break;
            }
        }
    }
    ThreadedNode *newNode = new (ThreadedNode);
    newNode->val = x;
    if (parentNode->val < x)
    {
        // x is greater than parent, insert right

        // 1. copy parent node's right and rbit to newnode
        newNode->right = parentNode->right;
        newNode->rbit = parentNode->rbit;

        // 2.
        newNode->lbit = 0;
        newNode->left = parentNode;

        // 3.
        parentNode->rbit = 1;
        parentNode->right = newNode;
    }
    else
    {
        // x is smaller than parent, insert left

        // 1. copy parent node's left and lbit to newnode
        newNode->left = parentNode->left;
        newNode->lbit = parentNode->lbit;

        // 2.
        newNode->rbit = 0;
        newNode->right = parentNode;

        // 3.
        parentNode->lbit = 1; // 0 -> 1
        parentNode->left = newNode;
    }
}

ThreadedNode *ThreadedBST::inorderSuccessor(ThreadedNode *node)
{
    ThreadedNode *succ = node->right;
    if (node->rbit == 1)
    {
        // Node has right child,
        // then go to leftmost child
        while (succ->lbit == 1)
        {
            succ = succ->left;
        }
    }
    return succ;
}

void ThreadedBST::inorder()
{
    ThreadedNode *currentNode = HEAD;
    while (true)
    {
        currentNode = inorderSuccessor(currentNode);
        if (currentNode == HEAD)
        {
            cout << "\n";
            return;
        }
        cout << currentNode->val << " ";
    }
}

void ThreadedBST::preorder()
{
    int flag = 1;
    ThreadedNode *currentNode = HEAD->left; // ROOT Node
    while (currentNode != HEAD)
    {
        while (flag != 0)
        { // Execute the loop until a thread is found
            cout << currentNode->val << " ";
            if (currentNode->lbit == 1)
            {
                currentNode = currentNode->left;
            }
            else
            {
                // currentNode -> lbit = 0, a thread is present, hence break the loop
                break;
            }
        }
        flag = currentNode->rbit;
        currentNode = currentNode->right;
    }
    cout << "\n";
}

void ThreadedBST::deleteNode(int x)
{
    ThreadedNode *parentNode = HEAD->left;
    ThreadedNode *currentNode = HEAD->left;
    while (currentNode->val != x)
    {
        parentNode = currentNode;
        if (currentNode->val > x)
        { // left
            if (currentNode->lbit == 1)
            {
                // left -> child
                currentNode = currentNode->left; // Go left
            }
        }
        else if (currentNode->val < x)
        { // x > currentNode -> val
            if (currentNode->rbit == 1)
            {                                     // right
                currentNode = currentNode->right; // Go right
            }
        }
    }
    deleteChildNode(parentNode, currentNode);
}

void ThreadedBST::deleteChildNode(ThreadedNode *parentNode, ThreadedNode *childNode)
{
    // We need to delete child node
    // Check for three cases

    if (childNode->lbit == 1 && childNode->rbit == 1)
    {
        // Deletion of node with two children
        // Find smallest value in right-subtree
        ThreadedNode *node = childNode->right; // Will represent smallest value in right-subtree
        while (node->lbit != 0)
        {
            node = node->left;
        }
        childNode->val = node->val;
        childNode = node;
        // childNode will not get deleted in any of the subsequent blocks
        // based on the number of children it has
    }

    if (childNode->lbit == 0 && childNode->rbit == 0)
    {
        // Deletion of node with no children i.e. leaf node
        if (parentNode->right == childNode)
        {
            // Transfer child's rbit and right thread to parent
            parentNode->rbit = childNode->rbit;
            parentNode->right = childNode->right;
        }
        else
        {
            // Transfer child's lbit and left thread to parent
            parentNode->lbit = childNode->lbit;
            parentNode->left = childNode->left;
        }
        delete childNode;
    }
    else
    {
        // Deletion of node with one child

        if (childNode->lbit == 1 && childNode->rbit == 0)
        {
            // Left child is node
            // Right child is a thread
            if (parentNode->left == childNode)
            {
                parentNode = childNode->left;
            }
            else if (parentNode->right == childNode)
            {
                parentNode = parentNode->right;
            }

            while (parentNode->rbit != 1)
            {
                parentNode = parentNode->right;
            }
            parentNode->right = childNode->right;
            delete childNode;
        }
        else if (childNode->lbit == 0 && childNode->rbit == 1)
        {
            // Left child is thread
            // Right child is a node
            if (parentNode->left == childNode)
            {
                parentNode = childNode->left;
            }
            else if (parentNode->right == childNode)
            {
                parentNode = parentNode->right;
            }
            while (parentNode->lbit != 1)
            {
                parentNode = parentNode->left;
            }
            parentNode->left = childNode->left;
            delete childNode;
        }
    }
}

int main()
{

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
    tree.preorder();

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