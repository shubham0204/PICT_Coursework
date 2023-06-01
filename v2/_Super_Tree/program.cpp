#include "queue.cpp"
#include "stack.cpp"
#include <iostream>
#include <cmath>
using namespace std ; 

class Node {

    int val ; 
    Node* left = nullptr ; 
    Node* right = nullptr ;

    public:

    friend class SuperTree ;

} ; 

class SuperTree {

    public:

    Node* ROOT = nullptr ; 

    void createTree( int values[] , int n ) {
        int i = 0 ; 
        ROOT = new( Node ) ; 
        ROOT -> val = values[ i ] ; 
        Queue<Node*> q ; 
        q.push( ROOT ) ; 

        while( i < n - 1 ) {

            Node* poppedNode = q.front() ; 
            q.pop() ; 

            if( values[ ++i ] != -1 ) {
                Node* leftNode = new( Node ) ; 
                leftNode -> val = values[ i ] ; 
                poppedNode -> left = leftNode ; 
                q.push( leftNode ) ; 
            }
            else {
                poppedNode -> left = nullptr ; 
            }

            if( values[ ++i ] != -1 ) {
                Node* rightNode = new( Node ) ;
                rightNode -> val = values[ i ] ; 
                poppedNode -> right = rightNode ; 
                q.push( rightNode ) ; 
            }
            else {
                poppedNode -> right = nullptr ; 
            }
            
        }
    }

    void iPreorder() {
        Stack<Node*> s ; 
        Node* currentNode = ROOT ;
        while( true ) {
            while( currentNode != nullptr ) {
                cout << currentNode -> val << " " ; 
                s.push( currentNode ) ; 
                currentNode = currentNode -> left ; 
            }
            if( s.empty() ) {
                cout << "\n" ; 
                return ; 
            }
            currentNode = s.top() -> right ; 
            s.pop() ; 
        }
    }

    void iPostorder() {
        Stack<Node*> s ; 
        Node* currentNode = ROOT ; 

        Node* temp = new( Node ) ; 
        temp -> val = -1 ; 

        while( true ) {
            while( currentNode != nullptr ) {
                s.push( currentNode ) ; 
                if( currentNode -> right != nullptr ) {
                    s.push( currentNode -> right ) ; 
                    s.push( temp ) ; 
                }
                currentNode = currentNode -> left ; 
            }
            currentNode = s.top() ; 
            s.pop() ; 
            while( currentNode -> val != -1 && !s.empty() ) {
                cout << currentNode -> val << " " ; 
                currentNode = s.top() ; 
                s.pop() ; 
            }
            if( s.empty() ) {
                cout << currentNode -> val << " \n" ; 
                return ; 
            }
            else {
                currentNode = s.top() ; 
                s.pop() ; 
            }
        }
    }

    void iInorder() {
        Stack<Node*> s ; 
        Node* currentNode = ROOT ; 
        while( true ) {
            while( currentNode != nullptr ){
                s.push( currentNode ) ; 
                currentNode = currentNode -> left ; 
            }
            if( s.empty() ) {
                cout << "\n" ; 
                return; 
            }
            currentNode = s.top() ; 
            s.pop() ; 
            cout << currentNode -> val << " " ; 
            currentNode = currentNode -> right ; 
        }
    }


    void breadthFirstTraversal() {
        Queue<Node*> q ; 
        q.push( ROOT ) ; 
        while( !q.empty() ) {

            Node* poppedNode = q.front() ; 
            q.pop() ;
            cout << poppedNode -> val << " " ; 

            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ; 
            }

            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ; 
            }

        }
        cout << "\n" ; 
    }

    int iGetHeight() {
        Queue<Node*> q ; 
        Queue<int> levels ; 
        q.push( ROOT ) ; 
        levels.push( 1 ) ; 
        int poppedLevel = 0 ;
        while( !q.empty() ) {
            Node* poppedNode = q.front() ; 
            poppedLevel = levels.front() ; 
            q.pop() ; 
            levels.pop() ; 
            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ; 
                levels.push( poppedLevel + 1 ) ; 
            }
            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ; 
                levels.push( poppedLevel + 1 ) ; 
            }
        }
        return poppedLevel ; 
    }

    void iCountLeafChildNodes() {
        Queue<Node*> q ; 
        q.push( ROOT ) ; 
        int leafNodes = 0 ;
        int internalNodes = 0 ; 
        while( !q.empty() ) {
            Node* poppedNode = q.front() ; 
            q.pop() ; 
            if( poppedNode -> left == nullptr && poppedNode -> right == nullptr ) {
                leafNodes++ ; 
            }
            else {
                internalNodes++ ; 
            }
            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ; 
            }
            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ; 
            }
        }
        cout << "Leaf nodes are " << leafNodes << "\n" ; 
        cout << "Internal nodes are " << internalNodes << "\n" ; 
    }

    void iDeleteAllNodes() {
        Queue<Node*> q ; 
        q.push( ROOT ) ; 
        while( !q.empty() ) {
            Node* poppedNode = q.front() ; 
            q.pop() ; 
            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ; 
            }
            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ; 
            }
            delete poppedNode ; 
        }
        ROOT = nullptr ; 
    }

    void iMirrorNodes() {
        Queue<Node*> q ; 
        q.push( ROOT ) ; 
        while( !q.empty() ) {
            Node* poppedNode = q.front() ; 
            Node* temp = poppedNode -> left ; 
            poppedNode -> left = poppedNode -> right ; 
            poppedNode -> right = temp ; 
            q.pop() ; 
            if( poppedNode -> left != nullptr ) {
                q.push( poppedNode -> left ) ; 
            }
            if( poppedNode -> right != nullptr ) {
                q.push( poppedNode -> right ) ;
            }
        }
    }

    void rPreorder( Node* node ) {
        if( node == nullptr ) {
            return ;
        }
        cout << node -> val << " " ; 
        rPreorder( node -> left ) ; 
        rPreorder( node -> right ) ; 
    }

    void rInorder( Node* node ) {
        if( node == nullptr ) {
            return ; 
        }
        rInorder( node -> left ) ;
        cout << node -> val << " " ; 
        rInorder( node -> right ) ; 
    }

    void rPostorder( Node* node ) {
        if( node == nullptr ) {
            return ; 
        }
        rPostorder( node -> left ) ;
        rPostorder( node -> right ) ; 
        cout << node -> val << " " ; 
    }

    int rGetHeight( Node* node ) {
        if( node == nullptr ) {
            return 0 ; 
        }
        int maxHeight = 1 + max( rGetHeight( node -> left ) , rGetHeight( node -> right ) ) ; 
        return maxHeight ; 
    }

    void rCountLeafChildNodes( Node* node , int& leafNodeCount , int& internalNodeCount ) {
        if( node == nullptr ) {
            return ; 
        }
        if( node -> left == nullptr && node -> right == nullptr ) {
            leafNodeCount++ ; 
        }
        else {
            internalNodeCount++ ; 
        }
        rCountLeafChildNodes( node -> left , leafNodeCount , internalNodeCount ) ; 
        rCountLeafChildNodes( node -> right , leafNodeCount , internalNodeCount ) ;
    }

    Node* rDeleteAllNodes( Node* node ) {
        if( node == nullptr ) {
            return nullptr ; 
        }
        node -> left = rDeleteAllNodes( node -> left ) ; 
        node -> right = rDeleteAllNodes( node -> right ) ; 
        delete node ; 
        return nullptr ; 
    }

    Node* rMirrorNodes( Node* node ) {
        if( node == nullptr ) {
            return nullptr ; 
        }
        node -> left = rMirrorNodes( node -> left ) ; 
        node -> right = rMirrorNodes( node -> right ) ; 
        Node* temp = node -> left ; 
        node -> left = node -> right ; 
        node -> right = temp ; 
        return node ; 
    }


} ; 

int main() {

    int values[7] = { 1 , 2 , 3 , -1 , 3 , 4 , -1 } ; 
    SuperTree tree ; 
    tree.createTree( values , 7 ) ; 
    tree.breadthFirstTraversal() ; 
    cout << "Iterative Traversals" << "\n" ;
    tree.iPreorder() ; 
    tree.iInorder() ; 
    tree.iPostorder() ; 
    cout << "Height of tree is " << tree.iGetHeight() << "\n" ; 
    tree.iCountLeafChildNodes() ; 

    tree.iMirrorNodes() ; 
    cout << "Mirrored BFS: " << "\n" ; 
    tree.breadthFirstTraversal() ; 
    
    cout << "Recursive Traversals" << "\n" ; 
    tree.rInorder( tree.ROOT ) ;
    cout << "\n" ; 
    tree.rPreorder( tree.ROOT ) ;
    cout << "\n" ; 
    tree.rPostorder( tree.ROOT ) ;
    cout << "\n" ; 
    cout << "Height of tree is " << tree.rGetHeight( tree.ROOT ) << "\n" ; 
    int childNodeCount = 0 ;
    int internalNodeCount = 0 ; 
    tree.rCountLeafChildNodes( tree.ROOT , childNodeCount , internalNodeCount ) ;
    cout << "Leaf nodes are " << childNodeCount << "\n" ; 
    cout << "Internal nodes are " << internalNodeCount << "\n" ; 
    tree.rMirrorNodes( tree.ROOT ) ; 
    tree.breadthFirstTraversal() ; 

    tree.iDeleteAllNodes() ; 
    // tree.rDeleteAllNodes( tree.ROOT ) ;

    return 0 ;
}