#include <iostream>

using namespace std;


// Base/Parent class
class Publication {

// Accessible in derived classes
protected:

	string title ;
	float price ;

public:

	// Default constructor
	Publication() {
		title = "" ;
		price = 0.0f ;
	}

	// Getter / Setter methods for accessing private member
	void setTitle( string title_ ) {
		title = title_ ;
	}
	void setPrice( float price_ ) {
		price = price_ ;
	}
	string getTitle() {
		return title ;
	}
	float getPrice() {
		return price ;
	}

	// Will be called by subclasses to print basic details of each publication
	void printPublication(){
		cout << "Title : " << title << endl ;
		cout << "Price : " << price << endl ;
	}

	void print();

};

// public derivation
// Public, protected members of base class are public, protected respectively
class Book : public Publication {

private:

	int pageCount ;

public:

	Book(){} ;

	// Getter / Setter methods for accessing private member
	int getPageCount() {
		return pageCount ;
	}
	void setPageCount( int count ) {
		pageCount = count ;
	}

	void print() {
		// Calling method of base class to print basic details
		Publication::printPublication() ;
		// Printing additional/specific details
		cout << "Page Count : " << pageCount << endl ;
	}

};

// public derivation
// Public, protected members of base class are public, protected respectively
class Tape : public Publication {

private:

	float playingTime ;

public:

	Tape(){} ;

	// Getter / Setter methods for accessing private member
	float getPlayingTime() {
		return playingTime ;
	}
	void setPlayingTime( float time ) {
		playingTime = time ;
	}

	void print() {
		// Calling method of base class to print basic details
		Publication::printPublication() ;
		// Printing additional/specific details
		cout << "Playing Time : " << playingTime << endl ;
	}

};

void checkPageCount( int count ) {
	if( count <= 0  ) {
		throw count ;
	}
}

void checkPlayingTime( float time ) {
	if( time <= 0  ) {
		throw time ;
	}
}


int main() {

	int numItems ;
	cout << "Enter number of items : " << endl ;
	cin >> numItems ;

	Publication items[ numItems ] ;
	for( int i = 0 ; i < numItems ; i++ ) {
		int option ;
		cout << "Enter (1) for Book and (2) for Tape : " << endl ;
		cin >> option ;
		if( option == 1 ) {
			try {
				string title;
				float price;
				int pageCount;
				cout << "Title -> " << endl ; 
				cin >> title ; 
				cout << "Price -> " << endl ; 
				cin >> price ; 
				cout << "Page Count -> " << endl ; 
				cin >> pageCount ; 

				// Can throw exception
				checkPageCount( pageCount ) ;

				Book book; 
				// Methods inherited from base class 
				book.setTitle(title);
				book.setPrice(price);
				// Method defined in subclass Book
				book.setPageCount(pageCount);
				items[i] = book;
				book.print() ; 
			}
			catch( int count ) {
				// Add publication with default values
				cout << "Invalid page count. Inserting default values for publication" << endl ;
				Book book;
				book.setTitle( "DefaultTitle");
				book.setPrice( 100.0f );
				book.setPageCount( 0 );
				items[ i ] = book ;
			}
		}
		else if ( option == 2 ){
			try {
				string title;
				float price;
				float time;
				cout << "Title -> " << endl ; 
				cin >> title ; 
				cout << "Price -> " << endl ; 
				cin >> price ; 
				cout << "Playing Time -> " << endl ; 
				cin >> time ; 

				// Can throw exception
				checkPlayingTime( time ) ;

				Tape tape;
				// Methods inherited from base class
				tape.setTitle(title);
				tape.setPrice(price);
				// Method defined in subclass Tape
				tape.setPlayingTime(time);
				items[i] = tape;
				tape.print() ; 
			}
			catch( float time ) {
				// Add publication with default values
				cout << "Invalid playing time. Inserting default values for publication" << endl ;
				Tape tape;
				tape.setTitle( "DefaultTitle" );
				tape.setPrice( 100.0f );
				tape.setPlayingTime( 0.0f );
				items[ i ] = tape ;
			}
		}
	}

	cout << " -------- Publications ----------- " << endl ;
	for( int i = 0 ; i < numItems ; i++ ) {
		items[ i ].printPublication() ;
	}

	return 0;
}
