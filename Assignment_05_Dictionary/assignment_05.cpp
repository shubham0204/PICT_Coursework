/*
 * Implement all the functions of a dictionary (ADT) using open
hashing technique: separate chaining using linked list Data: Set of
(key, value) pairs, Keys are mapped to values, Keys must be
comparable, and Keys must be unique. Standard Operations: Insert
(key, value), Find(key), Delete(key)
 */

#include <iostream>
#include <cstring>
using namespace std ;


struct Node {
	string word ;
    string meaning ;
    Node* next = nullptr ;
} ;

class Dictionary {

    Node** headNodes ;
    int tableSize ;

    int hash( string identifier ) {
    	int asciiSum = 0 ;
    	for( int i = 0 ; i < identifier.length() ; i++ ) {
    		asciiSum += int(identifier[i]) ;
    	}
    	return asciiSum % tableSize ;
    }

    void insertNode( Node* headNode , string word , string meaning ) {
        Node* currentNode = headNode ;
        while( currentNode -> next != nullptr ) {
            currentNode = currentNode -> next ;
        }
        Node* newNode = new( Node ) ;
        newNode -> next = nullptr ;
        newNode -> word = word ;
        newNode -> meaning = meaning ;
        currentNode -> next = newNode ;
    }

    void printLinkedList( Node* headNode ) {
        Node* currentNode = headNode ;
        while( currentNode != nullptr ) {
            cout.width( 10 ) ;
            cout << currentNode -> word << " " << currentNode -> meaning << "," ;
            currentNode = currentNode -> next ;
        }
    }

    Node* findLinkedList( Node* headNode , string word ) {
        Node* currentNode = headNode ; 
        while( currentNode -> next != nullptr ) {
            if( currentNode -> word == word ) {
                return currentNode ; 
            }
        }
        return nullptr ; 
    }

    void deleteLinkedList( int index , Node* headNode , string word ) {
    	if( headNode -> word == word ) {
    		Node* secondNode = headNode -> next ;
    		delete headNodes[ index ] ;
    		headNodes[ index ] = secondNode ;
    	}
    	else {
    		Node* currentNode = headNode ;
    		Node* prevNode = nullptr ;// Delete head node
    		while( currentNode -> next != nullptr ) {
    			if( currentNode -> word == word ) {
    				break ;
    			}
    			prevNode = currentNode ;
    			currentNode = currentNode -> next ;
    		}
    		prevNode -> next = currentNode -> next ;
    		delete currentNode ;
    	}
    }

    public:

    Dictionary( int tableSize ) {
        this -> tableSize = tableSize ;
        headNodes = new Node*[ tableSize ] ;
        for( int i = 0 ; i < tableSize ; i++ ) {
            headNodes[ i ] = nullptr ;
        }
    }

    void insert( string word , string meaning ) {
        int hashAddress = hash( word ) ;
        if( headNodes[ hashAddress ] == nullptr ) {
            Node* newNode = new( Node ) ;
            newNode -> next = nullptr ;
            newNode -> word = word ;
            newNode -> meaning = meaning ;
            headNodes[ hashAddress ] = newNode ;
        }
        else {
            insertNode( headNodes[ hashAddress ] , word , meaning ) ;
        }
    }

    void display() {
        for( int i = 0 ; i < tableSize ; i++ ) {
            cout.width( 5 ) ;
            cout << i << " " ;
            printLinkedList( headNodes[ i ] ) ;
            cout << "\n" ;
        }
    }

    void find( string word ) {
        int hashAddress = hash( word ) ;
        Node* node = findLinkedList( headNodes[ hashAddress ] , word ) ; 
        if( node == nullptr ) {
            cout << "Record not found" << "\n" ; 
        }
        else {
            cout << "Word: " << node -> word << "\n" ; 
            cout << "Meaning: " << node -> meaning << "\n" ;
        }
    }

    void deleteWord( string word ) {
    	int hashAddress = hash( word ) ;
    	deleteLinkedList( hashAddress , headNodes[ hashAddress ] , word ) ;
    }

} ;

int main() {

    Dictionary dict( 10 ) ;
    while( true ) {
        int option ; 
        cout << "Enter option: " << "\n" ; 
        cout << "1 -> Insert" << "\n" ; 
        cout << "2 -> Find" << "\n" ; 
        cout << "3 -> Delete" << "\n" ;  
        cout << "4 -> Display" << "\n" ;  
        cout << "0 -> Exit" << "\n" ; 
        cin >> option ; 

        if( option == 1 ) {
            string word , meaning ; 
            cout << "Enter word: " << "\n" ; cin >> word ; 
            cout << "Enter meaning: " << "\n" ; cin >> meaning ; 
            dict.insert( word , meaning ) ; 
        }
        else if( option == 2 ){
            string word ; 
            cout << "Enter word to find: " << "\n" ; 
            cin >> word ; 
            dict.find( word ) ; 
        }
        else if( option == 3 ) {
            string word ; 
            cout << "Enter word to find: " << "\n" ; 
            cin >> word ;
            dict.deleteWord( word ) ; 
        }
        else if( option == 4 ) {
            dict.display() ; 
        }
        else {
            break ; 
        }
    }

    return 0 ;
}
