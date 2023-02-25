#include <iostream>
#include "linkedstack.cpp"
#include "linkedqueue.cpp"
using namespace std ;

template <class E>
class BinaryTree ;

template <class E>
class TreeNode {
    E val ;
    TreeNode* left = nullptr ;
    TreeNode* right = nullptr ;
    friend class BinaryTree<E> ;
} ;

template <class E>
class BinaryTree {

    TreeNode<E>* ROOT ;
    LinkedQueue<TreeNode<E>*> nodes ;
    int numElements ; 

    public:

     enum Traversals {
        INORDER ,
        PREORDER ,
        POSTORDER
    } ;

    ~BinaryTree() {
        deleteAllNodes() ; 
    }

    // Creates a binary tree from the given array
    // The array holds the typical representation of a binary tree
    // Iteration over this array builds a binary tree with level-wise node insertion
    void create( E* elements , int n ) {

        // A pointer used to access elements from the array
        int elementPtr = 0 ;
        numElements = n ;

        // Initialize ROOT and set its value to elements[0]
        ROOT = new( TreeNode<E> ) ;
        ROOT -> val = elements[ elementPtr ] ;

        // Initialize a queue and push ROOT to it
        LinkedQueue<TreeNode<E>*> nodesQueue ; 
        nodesQueue.push( ROOT ) ;

        while( elementPtr < n - 1 && !nodesQueue.isEmpty() ) {
            // Get the front element from the queue and pop it
            TreeNode<E>* currentNode = nodesQueue.front() ; 
            nodesQueue.pop() ; 
            // Add left and right children to currentNode
            // with values taken from `elements` array
            TreeNode<E>* leftChild = new( TreeNode<E> ) ;
            leftChild -> val = elements[ ++elementPtr ] ; 
            TreeNode<E>* rightChild = new( TreeNode<E> ) ;
            rightChild -> val = elements[ ++elementPtr ] ;
            currentNode -> left = leftChild ; 
            currentNode -> right = rightChild ; 
            // Push the newly created children to the queue
            nodesQueue.push( leftChild ) ; 
            nodesQueue.push( rightChild ) ;
        }
    }

    void travel( Traversals t ) {
        switch( t ) {
            case INORDER:
                inorderTraversal() ; 
                break ; 
            case PREORDER:
                preorderTraversal() ; 
                break ; 
            case POSTORDER:
                postorderTraversal() ; 
                break ; 
        }
    }
    
    void preorderTraversal() {
       	LinkedStack<TreeNode<E>*> s ;
       	s.push( ROOT ) ;
       	while( !s.isEmpty()  ) {
       		TreeNode<E>* currentNode = s.top() ;
            s.pop() ; 
       		if( currentNode -> right != nullptr ) {
       			s.push( currentNode -> right ) ;
       		}
            cout << currentNode -> val << " " ;
       		if( currentNode -> left != nullptr ) {
       			s.push( currentNode -> left ) ;
       		}
       	}
        cout << "\n" ; 
    }

    void postorderTraversal() {
       	LinkedStack<TreeNode<E>*> s ;
        LinkedStack<E> output ; 
        s.push( ROOT ) ; 
       	while( !s.isEmpty() ) {
            TreeNode<E>* currentNode = s.top() ;
            s.pop() ; 
            output.push( currentNode -> val ) ;
       		if( currentNode -> left != nullptr ) {
       			s.push( currentNode -> left ) ;
       		}
       		if( currentNode -> right != nullptr ) {
       			s.push( currentNode -> right ) ;
       		}
       	}
        while( !output.isEmpty() ) {
            cout << output.top() << " " ; 
            output.pop() ; 
        }
        cout << "\n" ; 
    }

    void inorderTraversal() {
       	LinkedStack<TreeNode<E>*> s ;
       	TreeNode<E>* currentNode = ROOT ;
       	while( !s.isEmpty() || currentNode != nullptr ) {
            while( currentNode != nullptr ) {
                s.push( currentNode ) ; 
                currentNode = currentNode -> left ;
            }
       		currentNode = s.top() ;
            s.pop() ; 
            cout << currentNode -> val << " " ;
            currentNode = currentNode -> right ;
       	}
        cout << "\n" ; 
    }


    void mirror() {
		swapLeftRightChildren( ROOT ) ;
	}

	void swapLeftRightChildren( TreeNode<E>* currentNode ) {
		if( currentNode == nullptr ) {
			// Leaf node reached, end recursive calls
			return;
		}
		// Swap left and right nodes
		TreeNode<E>* leftNode = currentNode -> left ;
		currentNode -> left = currentNode -> right ;
		currentNode -> right = leftNode ;
		// Proceed to left and right subtrees
		swapLeftRightChildren( currentNode -> left ) ;
		swapLeftRightChildren( currentNode -> right ) ;
	}


    void longestLength() {
		LinkedStack<TreeNode<E>*> s ;
		TreeNode<E>* currentNode = ROOT ;
		int currentLevel = 0 ;
        TreeNode<E>* treeNodes[ numElements ] ;
        int lengths[ numElements ] ;
        int nodePtr = 0 ;
		while( currentNode != nullptr || !s.isEmpty() ) {
			if( currentNode != nullptr ) {
				// Keep travelling leftwards and stack all nodes travelled
				// Also, increase the level by 1
				s.push( currentNode ) ;
				lengths[ nodePtr ] = currentLevel++ ;
                treeNodes[ nodePtr ] = currentNode ;
                nodePtr++ ; 
				currentNode = currentNode -> left ;
			}
			else {
				// Check if parent node on the node has a right child
				// If the node does not have a right child, pop and check next node
				// in the stack
				currentNode = s.top() -> right ;
				s.pop() ;
				if( currentNode != nullptr ) {
					// The parent node had a right child,
					// decrement the level by 1
					currentLevel-- ;
				}
			}
		}
        int maxLengthIndex = -1 ; 
        int maxLength = -1 ; 
        for( int i = 0 ; i < nodePtr ; i++ ) {
            if( lengths[i] > maxLength ) {
                maxLength = lengths[ i ] ; 
                maxLengthIndex = i ; 
            } 
        }
        cout << "Longest length node: " << treeNodes[ maxLengthIndex ] -> val << " length= " << lengths[ maxLengthIndex ] << "\n" ; 
	}

    BinaryTree operator=( BinaryTree other ) {
        return other.copyTree() ; 
    }

    BinaryTree copyTree() {
        TreeNode<E>* newRoot = ROOT ; 
        E nodes[ numElements ] ;
        int nodesPtr = 0 ;
        LinkedQueue<TreeNode<E>*> q ;
        q.push( newRoot ) ;
        while( !q.isEmpty() ) {
            TreeNode<E>* currentNode = q.front() ; 
            q.pop() ; 
            nodes[ nodesPtr++ ] = currentNode -> val ; 
            if( currentNode -> left != nullptr ) {
                q.push( currentNode -> left ) ; 
            }
            if( currentNode -> right != nullptr ) {
                q.push( currentNode -> right ) ; 
            }
        }
        BinaryTree tree ; 
        tree.create( nodes , nodesPtr ) ; 
        return tree ;
    }

    void countNodes() {
        int internalNodes = 0 ; 
        int leafNodes = 0 ; 
        LinkedStack<TreeNode<E>*> s ;
    	TreeNode<E>* currentNode = ROOT ;
    	s.push( ROOT ) ;
    	while( !s.empty() ) {
    		TreeNode<E>* node = s.top() ;
    		s.pop() ;
    		if( node -> left == nullptr && node -> right == nullptr ) {
                leafNodes++ ; 
            }
            else {
                internalNodes++ ; 
            }
            if( node -> right != nullptr ) {
    			s.push( node -> right ) ;
    		}
    		if( node -> left != nullptr ) {
    			s.push( node -> left ) ;
    		}
    	}
        cout << "Internal nodes: " << internalNodes << "\n" ; 
        cout << "Leaf nodes: " << leafNodes << "\n" ; 
    }

    void deleteAllNodes() {
        LinkedStack<TreeNode<E>*> s ;
        LinkedStack<TreeNode<E>*> output ; 
        s.push( ROOT ) ; 
       	while( !s.isEmpty() ) {
            TreeNode<E>* currentNode = s.top() ;
            s.pop() ; 
            output.push( currentNode ) ;
       		if( currentNode -> left != nullptr ) {
       			s.push( currentNode -> left ) ;
       		}
       		if( currentNode -> right != nullptr ) {
       			s.push( currentNode -> right ) ;
       		}
       	}
        while( !output.isEmpty() ) {
            delete output.top() ; 
        }
        cout << "\n" ; 
    }

} ;

int main() {
    BinaryTree<int> tree;

    int nums[7] = { 1 , 2 , 3 , 4 , 5 , 6 , 7 } ; 
    tree.create( nums , 7 ) ; 

    tree.preorderTraversal() ;
	tree.inorderTraversal() ; 
    tree.postorderTraversal() ; 

    tree.longestLength() ; 

    BinaryTree<int> tree2 = tree.copyTree() ; 
    tree2.inorderTraversal() ; 

    tree.deleteAllNodes() ; 
    tree2.deleteAllNodes() ; 

    tree.inorderTraversal() ; 
    tree2.inorderTraversal() ; 
  

    return 0 ;
}
