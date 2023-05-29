/*
Name: Shubham Panchal
Roll no: 21356 - G3
Beginning with an empty binary tree, Construct binary tree by inserting the 
values in the order given. After constructing a binary tree perform following 
operations on it-
 Perform inorder, preorder and post order traversal
 Change a tree so that the roles of the left and right pointers are swapped at 
every node 
 Find the height of tree
 Copy this tree to another [operator=] 
 Count number of leaves, number of internal nodes. 
 Erase all nodes in a binary tree. 
(Implement both recursive and non-recursive methods)

*/

#include <iostream>
#include "linkedstack.cpp"
#include "linkedqueue.cpp"
using namespace std;

class TreeNode
{
    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    friend class BinaryTree;
};

class BinaryTree
{

    TreeNode *ROOT;
    LinkedQueue<TreeNode *> nodes;
    int numElements;

public:
    enum Traversals
    {
        INORDER,
        PREORDER,
        POSTORDER
    };

    ~BinaryTree()
    {
        deleteAllNodes();
    }

    // Creates a binary tree from the given array
    // The array holds the typical representation of a binary tree
    // Iteration over this array builds a binary tree with level-wise node insertion
    void create(int *elements, int n)
    {

        // A pointer used to access elements from the array
        int elementPtr = 0;
        numElements = n;

        // Initialize ROOT and set its value to elements[0]
        ROOT = new (TreeNode);
        ROOT->val = elements[elementPtr];

        // Initialize a queue and push ROOT to it
        LinkedQueue<TreeNode *> nodesQueue;
        nodesQueue.push(ROOT);

        while (elementPtr < n - 1 && !nodesQueue.isEmpty())
        {
            // Get the front element from the queue and pop it
            TreeNode *currentNode = nodesQueue.front();
            nodesQueue.pop();
            // Add left and right children to currentNode
            // with values taken from `elements` array
            TreeNode *leftChild = new (TreeNode);
            leftChild->val = elements[++elementPtr];
            TreeNode *rightChild = new (TreeNode);
            rightChild->val = elements[++elementPtr];
            currentNode->left = leftChild;
            currentNode->right = rightChild;
            // Push the newly created children to the queue
            nodesQueue.push(leftChild);
            nodesQueue.push(rightChild);
        }
    }

    void travel(Traversals t)
    {
        switch (t)
        {
        case INORDER:
            inorderTraversal();
            break;
        case PREORDER:
            preorderTraversal();
            break;
        case POSTORDER:
            postorderTraversal();
            break;
        }
    }

    void inorderTraversal()
    {
        LinkedStack<TreeNode *> s;
        TreeNode *currentNode = ROOT;
        while (true)
        {
            while (currentNode != nullptr)
            {
                s.push(currentNode);
                currentNode = currentNode->left;
            }
            if (s.isEmpty())
            {
                cout << "\n";
                return;
            }
            currentNode = s.top();
            s.pop();
            cout << currentNode->val << " ";
            currentNode = currentNode->right;
        }
        cout << "\n";
    }

    void postorderTraversal()
    {
        LinkedStack<TreeNode *> s;
        TreeNode *currentNode = ROOT;
        TreeNode *temp = new (TreeNode);
        temp->val = -1;
        while (true)
        {
            while (currentNode != nullptr)
            {
                s.push(currentNode);
                if (currentNode->right != nullptr)
                {
                    s.push(currentNode->right);
                    s.push(temp);
                }
                currentNode = currentNode->left;
            }
            if (s.isEmpty())
            {
                cout << "\n";
                return;
            }
            currentNode = s.top();
            s.pop();
            while (currentNode->val != -1 && !s.isEmpty())
            {
                cout << currentNode->val << " ";
                currentNode = s.top();
                s.pop();
            }
            if (!s.isEmpty())
            {
                currentNode = s.top();
                s.pop();
            }
            if (s.isEmpty())
            {
                cout << currentNode->val << " ";
                cout << "\n";
                return;
            }
        }
    }

    void preorderTraversal()
    {
        LinkedStack<TreeNode *> s;
        TreeNode *currentNode = ROOT;
        while (true)
        {
            while (currentNode != nullptr)
            {
                cout << currentNode->val << " ";
                if (currentNode->right != nullptr)
                {
                    s.push(currentNode->right);
                }
                currentNode = currentNode->left;
            }
            if (s.isEmpty())
            {
                cout << "\n";
                return;
            }
            currentNode = s.top();
            s.pop();
        }
    }

    void mirror()
    {
        swapLeftRightChildren(ROOT);
    }

    void swapLeftRightChildren(TreeNode *currentNode)
    {
        if (currentNode == nullptr)
        {
            // Leaf node reached, end recursive calls
            return;
        }
        // Swap left and right nodes
        TreeNode *leftNode = currentNode->left;
        currentNode->left = currentNode->right;
        currentNode->right = leftNode;
        // Proceed to left and right subtrees
        swapLeftRightChildren(currentNode->left);
        swapLeftRightChildren(currentNode->right);
    }

    void longestLength()
    {
        LinkedStack<TreeNode *> s;
        TreeNode *currentNode = ROOT;
        int currentLevel = 0;
        TreeNode *treeNodes[numElements];
        int lengths[numElements];
        int nodePtr = 0;
        while (currentNode != nullptr || !s.isEmpty())
        {
            if (currentNode != nullptr)
            {
                // Keep travelling leftwards and stack all nodes travelled
                // Also, increase the level by 1
                s.push(currentNode);
                lengths[nodePtr] = currentLevel++;
                treeNodes[nodePtr] = currentNode;
                nodePtr++;
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
        int maxLengthIndex = -1;
        int maxLength = -1;
        for (int i = 0; i < nodePtr; i++)
        {
            if (lengths[i] > maxLength)
            {
                maxLength = lengths[i];
                maxLengthIndex = i;
            }
        }
        cout << "Longest length node: " << treeNodes[maxLengthIndex]->val << " length= " << lengths[maxLengthIndex] << "\n";
    }

    void setRoot(TreeNode *root)
    {
        ROOT = root;
    }

    BinaryTree operator=(BinaryTree other)
    {
        BinaryTree tree;
        tree.setRoot(other.copyTree(ROOT));
        return tree;
    }

    TreeNode *copyTree(TreeNode *parentNode)
    {
        if (parentNode != nullptr)
        {
            TreeNode *parentNodeCopy = new (TreeNode);
            parentNodeCopy->val = parentNode->val;
            if (parentNode->left == nullptr)
            {
                parentNodeCopy->left = nullptr;
            }
            else
            {
                parentNodeCopy->left = copyTree(parentNode->left);
            }
            if (parentNode->right == nullptr)
            {
                parentNodeCopy->right = nullptr;
            }
            else
            {
                parentNodeCopy->right = copyTree(parentNode->right);
            }
            return parentNodeCopy;
        }
        else
        {
            return nullptr;
        }
    }

    BinaryTree copyTreeIterative()
    {
        TreeNode *newRoot = ROOT;
        int nodes[numElements];
        int nodesPtr = 0;
        LinkedQueue<TreeNode *> q;
        q.push(newRoot);
        while (!q.isEmpty())
        {
            TreeNode *currentNode = q.front();
            q.pop();
            nodes[nodesPtr++] = currentNode->val;
            if (currentNode->left != nullptr)
            {
                q.push(currentNode->left);
            }
            if (currentNode->right != nullptr)
            {
                q.push(currentNode->right);
            }
        }
        BinaryTree tree;
        tree.create(nodes, nodesPtr);
        return tree;
    }

    void countNodes()
    {
        int internalNodes = 0;
        int leafNodes = 0;
        LinkedStack<TreeNode *> s;
        s.push(ROOT);
        while (!s.isEmpty())
        {
            TreeNode *node = s.top();
            s.pop();
            if (node->left == nullptr && node->right == nullptr)
            {
                leafNodes++;
            }
            else
            {
                internalNodes++;
            }
            if (node->right != nullptr)
            {
                s.push(node->right);
            }
            if (node->left != nullptr)
            {
                s.push(node->left);
            }
        }
        cout << "Internal nodes: " << internalNodes << "\n";
        cout << "Leaf nodes: " << leafNodes << "\n";
    }

    void deleteAllNodes()
    {
        LinkedStack<TreeNode *> s;
        LinkedStack<TreeNode *> output;
        s.push(ROOT);
        while (!s.isEmpty())
        {
            TreeNode *currentNode = s.top();
            s.pop();
            output.push(currentNode);
            if (currentNode->left != nullptr)
            {
                s.push(currentNode->left);
            }
            if (currentNode->right != nullptr)
            {
                s.push(currentNode->right);
            }
        }
        while (!output.isEmpty())
        {
            delete output.top();
            output.pop();
        }
        cout << "\n";
    }
};

int main()
{
    BinaryTree tree;
    while (true)
    {
        int option;
        cout << "Enter option: "
             << "\n";
        cout << "1. Creation and insertion"
             << "\n";
        cout << "2. Preorder Traversal"
             << "\n";
        cout << "3. Inorder Traversal"
             << "\n";
        cout << "4. Postorder Traversal"
             << "\n";
        cout << "5. Swap nodes"
             << "\n";
        cout << "6. Find Height"
             << "\n";
        cout << "7. Count leaf and internal nodes"
             << "\n";
        cout << "8. Copy tree"
             << "\n";
        cout << "9. Erase all"
             << "\n";
        cin >> option;
        if (option == 1)
        {
            int nums[7] = {1, 2, 3, 4, 5, 6, 7};
            tree.create(nums, 7);
        }
        else if (option == 2)
        {
            tree.inorderTraversal();
        }
        else if (option == 3)
        {
            tree.preorderTraversal();
        }
        else if (option == 4)
        {
            tree.postorderTraversal();
        }
        else if (option == 5)
        {
            tree.mirror();
        }
        else if (option == 6)
        {
            tree.longestLength();
        }
        else if (option == 7)
        {
            tree.countNodes();
        }
        else if (option == 8)
        {
            tree = tree ;
        }
        else if (option == 9)
        {
            tree.deleteAllNodes();
        }
    }

    return 0;
}
