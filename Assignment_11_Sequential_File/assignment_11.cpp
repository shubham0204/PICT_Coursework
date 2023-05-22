#include <iostream>
#include <fstream>
#include <ios>
#include <vector>
#include <cstring>
using namespace std;

class Record {

	int rollNumber ;
	string name ;
	char division ;
	string address ;

public:

	Record( int rollNumber , string name , char division , string address ){
		this -> rollNumber = rollNumber ;
		this -> name = name ;
		this -> division = division ;
		this -> address = address ;
	}

	friend class SequentialFile ;

};

class SequentialFile {

	string filename ;
	fstream inputStream ;
	fstream outputStream ;

public:

	SequentialFile( string filename ) {
		this -> filename = filename ;
	}

	void writeRecords( Record records[] , int n ) {
		// Open the filestream and append records line-by-line
		outputStream.open( filename , ios::out ) ;
		for( int i = 0 ; i < n ; i++ ) {
			outputStream << records[i].rollNumber << "," << records[i].name << "," << records[i].division << "," << records[i].address + "\n"  ;
		}
		outputStream.close() ;
 	}

	void printRecords() {
		// Open the filestream in ios::in mode and read records line-by-line
		inputStream.open( filename , ios::in ) ;
		while( !inputStream.eof() ) {
			string record ;
			inputStream >> record ;
			cout << record << endl;
		}
		inputStream.close() ;
	}

	void searchRecord( int rollNumber ) {
		// Search the record for rollNumber line-by-line
		inputStream.open( filename , ios::in ) ;
		bool isFound = false ;
		while( !inputStream.eof() ) {
			string record ;
			inputStream >> record ;
			if( (int(record[0]) - 48) == rollNumber ) {
				cout << "Record found" << "\n" ;
				cout << record << "\n" ;
				isFound = true ;
				break;
			}
		}
		if( !isFound ) {
			cout << "Record not found" << "\n" ;
		}
		inputStream.close() ;
	}

	void deleteRecord( int rollNumber ) {
		// Append lines for the records whose
		// rollnumber does not equal the given number
		// in the list `lines`
		inputStream.open( filename , ios::in ) ;
		vector<string> lines ;
		while( !inputStream.eof() ) {
			string record ;
			inputStream >> record ;
			if( (int(record[0]) - 48) != rollNumber ) {
				lines.push_back( record ) ;
			}
		}
		inputStream.close() ;
		// Clear all contents of the file (by opening it in ios::out mode)
		// and rewrite all files
		outputStream.open( filename , ios::out ) ;
		for( int i = 0 ; i < lines.size() ; i++ ) {
			outputStream << lines[ i ] << "\n" ;
		}
		outputStream.close() ;
	}



};

int main() {
	SequentialFile file( "contents.txt" ) ;
	Record records[3] = {
			Record( 6 , "Shubham" , '3' , "Katraj" ) ,
			Record( 5 , "Kaustubh" , '3' , "Katraj" ) ,
			Record( 3 , "Advait" , '3' , "NYC" )
	} ;
	file.writeRecords( records , 3 ) ;
	file.printRecords() ;
	file.searchRecord( 1 ) ;
	file.deleteRecord( 6 ) ;
	file.printRecords() ;
	return 0;
}
