#include <iostream>
#include <queue>
#include <stack>
using namespace std ;

class TreeNode {

    int val ; 
    TreeNode* left = nullptr ; 
    TreeNode* right = nullptr ; 

    public:

    friend class BinaryTree ; 

} ; 

class BinaryTree {

    TreeNode* ROOT = nullptr ;

    public:

    void createTree( int nodeValues[] , int n ) { 
        ROOT = new( TreeNode ) ; 
        ROOT -> val = nodeValues[ 0 ] ;
        int i = 0 ;
        queue<TreeNode*> q ;
        q.push( ROOT ) ;
        while( i < n - 1 ) {
            TreeNode* p = q.front() ;
            cout << p -> val << "\n" ; 
            q.pop() ;
            TreeNode* left = new( TreeNode ) ;
            left -> val = nodeValues[ ++i ] ;
            TreeNode* right = new( TreeNode ) ;
            right -> val = nodeValues[ ++i ] ;
            p -> left = left ;
            p -> right = right ;
            q.push( left ) ; 
            q.push( right ) ;
        }
    }

    void inorderTraversal() {
        stack<TreeNode*> s ; 
        TreeNode* curr = ROOT ; 
        while( true ) {
            while( curr != nullptr ) {
                s.push( curr ) ; 
                curr = curr -> left ; 
            }
            if( s.empty() ) {
                cout << "\n" ; 
                break ; 
            }
            curr = s.top() ; 
            s.pop() ; 
            cout << curr -> val << " " ; 
            curr = curr -> right ; 
        }
    }

    void preorderTraversal() {
        stack<TreeNode*> s ; 
        TreeNode* curr = ROOT ; 
        while( true ) {
            while( curr != nullptr ) {
                cout << curr -> val << " " ; 
                if( curr -> right != nullptr ) {
                    s.push( curr -> right ) ; 
                }
                curr = curr -> left ; 
            }
            if( s.empty() ) {
                cout << "\n" ; 
                return ; 
            }
            curr = s.top() ; 
            s.pop() ; 
            
        }
    }

    void postorderTraversal() {
        stack<TreeNode*> s ; 
        TreeNode* curr = ROOT ; 
        TreeNode* temp = new( TreeNode ) ; 
        temp -> val = -1 ; 
        while( true ) {
            while( curr != nullptr ) {
                s.push( curr ) ; 
                if( curr -> right != nullptr ) {
                    s.push( curr -> right ) ; 
                    s.push( temp ) ; 
                }
                curr = curr -> left ; 
            }
            if( s.empty() ) {
                cout << "\n" ; 
                return ; 
            }
            curr = s.top() ; 
            s.pop() ; 
            while( curr -> val != -1 && !s.empty() ) {
                cout << curr -> val << " " ; 
                curr = s.top() ; 
                s.pop() ; 
            }
            if( !s.empty() ) {
                curr = s.top() ; 
                s.pop() ; 
            }
            else {
                cout << curr -> val << "\n" ; 
                return ; 
            }
        }
    }

    void height() {
        queue<TreeNode*> q ;
        queue<int> levels ; 
        q.push( ROOT ) ; 
        levels.push( 1 ) ; 

        vector<int> lengths ;

        while( !q.empty() ) {
            TreeNode* p = q.front() ; 
            int l = levels.front() ; 
            q.pop() ; 
            levels.pop() ; 
            lengths.push_back( l ) ; 

            if( p -> left != nullptr ) {
                q.push( p -> left )  ;
                levels.push( l + 1 ) ; 
            }
            if( p -> right != nullptr ) {
                q.push( p -> right )  ;
                levels.push( l + 1 ) ; 
            }
        }

        int maxLevel = 0 ; 
        for( int level : lengths ) {
            if( maxLevel < level ) {
                maxLevel = level ; 
            }
        }
        cout << "Height of tree is " << maxLevel << "\n" ; 
    }

    void countNodes() {
        queue<TreeNode*> q ; 
        q.push( ROOT ) ; 
        int numLeaves = 0 ;
        int numInternal = 0 ;
        while( !q.empty() ) {
            TreeNode* p = q.front() ; 
            q.pop() ; 
            if( p -> left != nullptr && p -> right != nullptr ) {
                numInternal++ ; 
            } 
            if( p -> left == nullptr && p -> right == nullptr ) {
                numLeaves++ ; 
            }
            if( p -> left != nullptr ) {
                q.push( p -> left ) ; 
            }
            if( p -> right != nullptr ) {
                q.push( p -> right ) ; 
            }
        }
        cout << "Num leaf nodes: " << numLeaves << "\n" ; 
        cout << "Num internal nodes: " << numInternal << "\n" ; 
    }


    void deleteAllNodes() {
        queue<TreeNode*> q ; 
        q.push( ROOT ) ; 
        while( !q.empty() ) {
            TreeNode* p = q.front() ; 
            q.pop() ; 
            if( p -> left != nullptr ) {
                q.push( p -> left ) ; 
            }
            if( p -> right != nullptr ) {
                q.push( p -> right ) ;
            }
            delete p ; 
        }
    }



} ; 

int main() {

    BinaryTree tree ; 
    int values[ 9 ] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 0 } ;
    tree.createTree( values , 9 ) ; 
    tree.inorderTraversal() ; 
    tree.preorderTraversal() ; 
    tree.postorderTraversal() ; 
    tree.countNodes() ; 
    tree.height() ; 

    tree.deleteAllNodes() ; 

    return 0 ; 
}