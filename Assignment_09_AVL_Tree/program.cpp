/*
A Dictionary stores keywords & its meanings.Provide facility for adding new keywords, deleting keywords,
updating values of any entry.Provide facility to display whole data sorted in ascending/Descending order.
Also find how many maximum comparisons may require for finding any keyword.Use Height balance tree and
find the complexity for finding a keyword.

Name : Advait Naik
Roll No : 21354
*/

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Node{
    int key, height = 1;
    Node *left, *right;

public:
    Node(int val){
        this -> key = val;
        this -> left = nullptr;
        this -> right = nullptr;
    }

    friend class AVL;
};

class AVL{
    Node *root = nullptr;

    int getHeight(Node *node){
        if(node == nullptr){
            return 0;
        }
        return node -> height;
    }

    void changeHeight(Node *node){
        node -> height = 1 + max(getHeight(node -> left) , getHeight(node -> right));
    }

    int balanceFactor(Node *node){
        if(node == nullptr){
            return 0;
        }
        return getHeight(node -> left) - getHeight(node -> right);
    }

    Node *llRotation(Node *node){
        Node *newRoot = node -> left;
        node -> left = newRoot -> right;
        newRoot -> right = node;

        changeHeight(node);
        changeHeight(newRoot);
        return newRoot;
    }

    Node *rrRotation(Node *node){
        Node *newRoot = node -> right;
        node -> right = newRoot -> left;
        newRoot -> left = node;

        changeHeight(node);
        changeHeight(newRoot);
        return newRoot;
    }

    Node *lrRotation(Node *node){
        node -> left = rrRotation(node -> left);
        return llRotation(node);
    }

    Node *rlRotation(Node *node){
        node -> right = llRotation(node -> right);
        return rrRotation(node);
    }

    Node *balanceNode(Node *node){
        if(balanceFactor(node) == 2){
            if(balanceFactor(node -> left) < 0){
                node = lrRotation(node);
            }
            else{
                node = llRotation(node);
            }
        }
        else if(balanceFactor(node) == -2){
            if(balanceFactor(node -> right) > 0){
                node = rlRotation(node);
            }
            else{
                node = rrRotation(node);
            }
        }

        changeHeight(node);
        return node;
    }

    Node *insertNode(Node *node,int val){
        if(node == nullptr){
            node = new Node(val);
            return node;
        }

        if(val < node -> key){
            node -> left = insertNode(node -> left,val);
        }
        else if(val > node -> key){
            node -> right = insertNode(node -> right,val);
        }
        else{
            return node;
        }
        return balanceNode(node);
    }

    Node *deleteNode(Node *node,int x){
        if(node == nullptr){
            return nullptr;
        }

        if(node -> key == x){
            if(node -> right != nullptr && node -> left != nullptr){
                Node *smallestRST = node -> right;
                while(smallestRST -> left != nullptr){
                    smallestRST = smallestRST -> left;
                }
                node -> key = smallestRST -> key;
                node -> right = deleteNode(node -> right,smallestRST -> key);
            }

            if(node -> key == x && node -> left == nullptr && node -> right != nullptr){
                Node *rightChild = node -> right;
                delete node;
                return rightChild;
            }
            else if(node -> key == x && node -> left != nullptr && node -> right == nullptr){
                Node *leftChild = node -> left;
                delete node;
                return leftChild;
            }
            else if(node -> key == x){
                delete node;
                return nullptr;
            }
        }
        else{
            if(x < node -> key){
                node -> left = deleteNode(node -> left,x);
            }
            else{
                node -> right = deleteNode(node -> right,x);
            }
        } 

        int bf = balanceFactor(node);
        if(bf != 2 && bf != -2){
            return node;
        } 
        else{
            node = balanceNode(node);
            return node;
        }
    }

    Node* search( int value ) {
        Node* current = this -> root ; 

        while( current != nullptr ) {
            if( current -> key > value ) {
                current = current -> left ; 
            }
            else if( current -> key < value ) {
                current = current -> right ; 
            }
            else {
                return current ; 
            }
        }

        return nullptr ; 
    }

public:
    void insert(int val){
        this -> root = insertNode(this -> root,val);
    }

    void bfs(){
        queue <Node *> q;
        q.push(this -> root);

        while(!q.empty()){
            Node *current = q.front();
            cout<<current -> key<<" ";
            q.pop();

            if(current -> left != nullptr){
                q.push(current -> left);
            }
            if(current -> right != nullptr){
                q.push(current -> right);
            }
        }
        cout<<endl;
    }

    void deleteKey(int val){
        this -> root = deleteNode(this -> root , val);
    }

    void searchKey(int val){
        Node *ans = search(val);
        if(ans == nullptr){
            cout<<"Key not present in tree."<<endl;
        }
        else{
            cout<<"Key present in tree."<<endl;
        }
    }        
};

int main(){
    AVL t;
    t.insert(23);
    t.insert(12);
    t.insert(46);
    t.insert(57);
    t.insert(90);
    t.bfs();

    t.searchKey(57);
    t.searchKey(11);

    t.deleteKey(23);
    t.bfs();

    return 0;
}