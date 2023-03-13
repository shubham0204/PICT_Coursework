/*
 * Consider telephone book database of N clients. Make use of a hash
table implementation to quickly look up client’s telephone number.
Make use of two collision handling techniques and compare them using
number of comparisons required to find a set of telephone numbers
(Note: Use linear probing with replacement and without replacement)
 */

#include <iostream>
#include <ios>
#include <cstring>
using namespace std;

// Represents an entry in the HashTable
// Each key will be mapped to a Record
class Record {

	char clientName[ 20 ] ;
	int telephone ;

public:

	Record() {
		// Created empty record with default values
		strcpy( clientName , "----" ) ;
		telephone = 0 ;
	}

	Record( char name[] , int telephone ) {
		strcpy( clientName , name ) ;
		this -> telephone = telephone ;
	}

	void printRecord() {
		cout.width( 20 ) ;
		cout << clientName << " " ;
		cout.width( 20 ) ;
		cout << telephone << "\n" ;
	}

	bool isEmpty() {
		// Check if current record is default or populated
		return telephone == 0 ;
	}

	friend class HashTable ;
};

class HashTable {

	int tableSize ;
	Record* records;

	// Hash function which maps clientName to a unique integer
	// Defined by hash( clientName ) = SUM mod TABLESIZE
	// where  SUM -> Sum of all ASCII values of chars in clientName
	//        TABLESIZE -> Size of the HashTable
	int hash( char clientName[] ) {
		int asciiSum = 0 ;
		char c = clientName[0] ;
		for( int i = 0 ; c != '\0' ; i++ ) {
			asciiSum += clientName[i] ;
			c = clientName[++i] ;
		}
		return asciiSum % tableSize ;
	}

public:

	HashTable( int tableSize ) {
		this -> tableSize = tableSize ;
		records = new Record[ tableSize ] ;
	}

	void createTable() {
		for( int i = 0 ; i < (this->tableSize) ; i++ ) {
			records[ i ] = Record() ;
		}
	}

	void displayTable() {
		cout.width( 20 ) ;
		cout << "Client Name  " ;
		cout.width( 20 ) ;
		cout << "Telephone  " << "\n" ;
		for( int i = 0 ; i < (this->tableSize) ; i++ ) {
			cout << i << " " ;
			records[ i ].printRecord() ;
		}
	}

	void insertRecord( Record newRecord ) {
		int index = hash( newRecord.clientName ) ;
		if( records[ index ].isEmpty() ) {
			records[ index ] = newRecord ;
		}
		else {
			// Handle Collision with linear probing technique
			// Increment a counter `currentIndex` which searchs for the
			// next empty record
			int currentIndex = index ;
			while( !records[ currentIndex ].isEmpty() ) {
				currentIndex = ( currentIndex + 1 ) % tableSize ;
			}
			records[ currentIndex ] = newRecord ;
		}
	}

	void searchRecord( char clientName[] ) {
		int index = hash( clientName ) ;
		if( strcmp( clientName , records[ index ].clientName ) == 0  ) {
			records[ index ].printRecord() ; 
		}
		else {
			int currentIndex = index ;
			int iterateCount = 0 ; 
			while( records[ currentIndex ].clientName != clientName ) {
				if( iterateCount >= tableSize ) {
					cout << "Record not found." << "\n" ; 
					break; 
				}
				else {
					currentIndex = ( currentIndex + 1 ) % tableSize ;
				}
				iterateCount++ ; 
			}
			records[ currentIndex ].printRecord() ;
		}
	}

};

int main() {
	HashTable table( 10 ) ;
	table.createTable() ;
	table.insertRecord( Record( "Shubham" , 987987 ) ) ;
	table.insertRecord( Record( "PICT" , 7234234) ) ;
	table.displayTable() ;
	table.searchRecord( "Shubham" ) ;
	table.searchRecord( "PICT" ) ;
	//table.searchRecord( "Shubham2" ) ;
	return 0;
}
