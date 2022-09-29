#include <iostream>

using namespace std;

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
	virtual void printPublication() {
		cout << "Base called " << endl ;
	}

};

// public derivation
// Public, protected members of base class are public, protected respectively
class Book : public Publication {

private:

	int pageCount ;

public:

	// Getter / Setter methods for accessing private member
	int getPageCount() {
		return pageCount ;
	}
	void setPageCount( int count ) {
		pageCount = count ;
	}

	// Virtual Function overriding
	void printPublication() override {
		cout << "Title : " << title << endl ;
		cout << "Price : " << price << endl ;
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

	// Function overriding
	void printPublication() override {
		cout << "Title : " << title << endl ;
		cout << "Price : " << price << endl ;
		cout << "Playing Time : " << playingTime << endl ;
	}

};

// Checks if title is not empty and raises an exception if true
void checkArgs( string title ) {
	if( title == "" ) {
		throw title ; 
	}
}


int main() {

	int numItems ;
	cout << "Enter number of items : " << endl ;
	cin >> numItems ;

	Publication* items[ numItems ] ;
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
				checkArgs( title ) ; 

				Book* book = new( Book ) ; 
				book -> setTitle(title);
				book -> setPrice(price);
				book -> setPageCount(pageCount);
				items[i] = book;
			}
			catch( string badTitle ) {
				cout << "Invalid title. Inserting default values for publication" << endl ;
				Publication publication ;
				publication.setTitle( "DefaultTitle" ) ; 
				publication.setPrice( 100.0f ) ; 
				items[ i ] = &publication ; 
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
				checkArgs( title ) ; 

				Tape tape;
				tape.setTitle(title);
				tape.setPrice(price);
				tape.setPlayingTime(time);
				items[i] = &tape;
			}
			catch( string badTitle ) {
				cout << "Invalid title. Inserting default values for publication" << endl ;
				Publication publication ;
				publication.setTitle( "DefaultTitle" ) ; 
				publication.setPrice( 100.0f ) ; 
				items[ i ] = &publication ; 
			}
		}
	}

	cout << "Items are : " << endl ;
	for( int i = 0 ; i < numItems ; i++ ) {
		items[ i ] -> printPublication() ; 
	}

	return 0;
}
