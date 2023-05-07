//============================================================================
// Name        : DSALab_PR_09_AVLTree.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

struct Node
{
    int key;
    string value;
    int height;
    Node* left;
    Node* right;

    Node(int k, const string& v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
};

int height(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int balanceFactor(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void updateHeight(Node* node)
{
    node->height = 1 + max(height(node->left), height(node->right));
}

Node* rotateLeft(Node* node)
{
    cout<<"------LL Rotation Applied-------"<< endl;

    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateRight(Node* node)
{
    cout<<"------RR Rotation Applied-------"<< endl;

    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateLeftRight(Node* node)
{
    cout<<"------RL Rotation Applied-------"<< endl;

    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* rotateRightLeft(Node* node)
{
    cout<<"------LR Rotation Applied-------"<< endl;

    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node* balance(Node* node)
{
    if (balanceFactor(node) == 2)
    {
        if (balanceFactor(node->left) < 0)
        {
            node = rotateLeftRight(node);
        }
        else
        {
            node = rotateRight(node);
        }
    }
    else if (balanceFactor(node) == -2)
    {
        if (balanceFactor(node->right) > 0)
        {
            node = rotateRightLeft(node);
        }
        else
        {
            node = rotateLeft(node);
        }
    }
    updateHeight(node);
    return node;
}

Node* insert(Node* node, int key, const string& value)
{
    if (node == nullptr)
    {
        return new Node(key, value);
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, value);
    }
    else
    {
        node->value = value; // key already exists, update value
        return node;
    }
    return balance(node);
}

bool search(Node* node, int key)
{
    if (node == nullptr)
    {
        return false;
    }
    if (key < node->key)
    {
        return search(node->left, key);
    }
    else if (key > node->key)
    {
        return search(node->right, key);
    }
    else
    {
        return true;
    }
}

void inorderTraversal(Node* node)
{
    if (node == nullptr)
    {
        return;
    }
    inorderTraversal(node->left);
    cout << node->key << ": " << node->value << " ";
    inorderTraversal(node->right);
}

void levelTraversal(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    Node* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front != rear)
    {
        Node* node = queue[front++];
        cout << node->key << ": " << node->value << " ";
        if (node->left != nullptr)
        {
            queue[rear++] = node->left;
        }
        if (node->right != nullptr)
        {
            queue[rear++] = node->right;
        }
    }
}

int main()
{
	int key;
	string value;

    Node* root = NULL;
    int choice = 0;

    do
    {
        cout << "Menu" << endl;
        cout << "1. Insert key-value pair" << endl;
        cout << "2. Search key" << endl;
        cout << "3. Level order traversal" << endl;
        cout << "4. Inorder traversal" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:


                cout << "Enter key: ";
                cin >> key;
                cout << "Enter value: ";
                cin >> value;
                root = insert(root, key, value);
                cout << "Inserted key-value pair: " << key << ": " << value << endl;
                break;

            case 2:

                cout << "Enter key to search: ";
                cin >> key;
                if (search(root, key))
                {
                    cout << "Key found!" << endl;
                }
                else
                {
                    cout << "Key not found." << endl;
                }
                break;

        case 3:
                cout << "Level order traversal: ";
                levelTraversal(root);
                cout << endl;
                break;


            case 4:

                cout << "Inorder traversal: ";
                inorderTraversal(root);
                cout << endl;
                break;

            case 5:
                cout << "Quitting program." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}


/*
 Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 10
Enter value: ten
Inserted key-value pair: 10: ten

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 5
Enter value: five
Inserted key-value pair: 5: five

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 3
Enter value: three
------RR Rotation Applied-------
Inserted key-value pair: 3: three

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 3
Level order traversal: 5: five 3: three 10: ten 

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 4
Inorder traversal: 3: three 5: five 10: ten 

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 12
Enter value: twelve
Inserted key-value pair: 12: twelve

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 14
Enter value: fourteen
------LL Rotation Applied-------
Inserted key-value pair: 14: fourteen

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 3
Level order traversal: 5: five 3: three 12: twelve 10: ten 14: fourteen 

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 4
Inorder traversal: 3: three 5: five 10: ten 12: twelve 14: fourteen 

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 1
Enter value: one
Inserted key-value pair: 1: one

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 2
Enter value: two
------RL Rotation Applied-------
------LL Rotation Applied-------
------RR Rotation Applied-------
Inserted key-value pair: 2: two

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 3
Level order traversal: 5: five 2: two 12: twelve 1: one 3: three 10: ten 14: fourteen 

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 4
Inorder traversal: 1: one 2: two 3: three 5: five 10: ten 12: twelve 14: fourteen 

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 18
Enter value: eighteen

Inserted key-value pair: 18: eighteen

Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 1
Enter key: 16
Enter value: sixteen
------LR Rotation Applied-------
------RR Rotation Applied-------
------LL Rotation Applied-------
Inserted key-value pair: 16: sixteen


Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit

Enter your choice: 3
Level order traversal: 5: five 2: two 12: twelve 1: one 3: three 10: ten 16: sixteen 14: fourteen 18: eighteen 


Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit


Enter your choice: 4
Inorder traversal: 1: one 2: two 3: three 5: five 10: ten 12: twelve 14: fourteen 16: sixteen 18: eighteen 


Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit


Enter your choice: 2
Enter key to search: 12
Key found!


Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit


Enter your choice: 2
Enter key to search: 99
Key not found.


Menu
1. Insert key-value pair
2. Search key
3. Level order traversal
4. Inorder traversal
5. Quit


Enter your choice: 5
Quitting program.
 
 */

