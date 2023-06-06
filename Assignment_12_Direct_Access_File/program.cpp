/*
Implementation of a direct access file -Insertion and deletion of a record from a 
direct access file
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std ; 

class Employee {

    int id ; 
    string name ; 
    int experience ; 
    int salary ;

    public:

    Employee( int id , string name , int experience , int salary ) {
        this -> id = id ; 
        this -> name = name ; 
        this -> experience = experience ; 
        this -> salary = salary ; 
    }

    string toString() {
        string output ; 
        return output + to_string( id ) + "-" + name + "-" + to_string( experience ) + "-" + to_string( salary ); 
    }

    friend class DirectAccessFile ; 

} ; 

class DirectAccessFile {

    int tableSize ; 
    string filename ; 
    int* hashTable = nullptr ; 

    int hash( int employeeId ) {
        return employeeId % tableSize ; 
    }

    public:

    DirectAccessFile( string filename , int tableSize ) {
        this -> filename = filename ; 
        this -> tableSize=  tableSize ; 
        this -> hashTable = new int[ this -> tableSize ] ;
        for( int i = 0 ; i < tableSize ; i++ ) {
            hashTable[ i ] = -1 ; 
        }   
    }

    void insertRecord( Employee e ) {
        ofstream outputStream ; 
        outputStream.open( filename , ios::app ) ; 
        int address = outputStream.tellp() ; 
        int hashAddress = hash( e.id ) ; 
        hashTable[ hashAddress ] = address ;
        outputStream.write( e.toString().c_str() , e.toString().length() );
        outputStream.write( "\n" , 1 ) ; 
        outputStream.close() ; 
    } 

    void searchRecord( int id ) {
        int hashAddress = hash( id ) ; 
        int recordAddress = hashTable[ hashAddress ] ; 

        if( recordAddress != -1 ) {
            ifstream inputStream ; 
            inputStream.open( filename , ios::in ) ; 
            inputStream.seekg( recordAddress , ios::beg ) ; 
    
            string recordLine = "" ; 
            char c = inputStream.get() ; 
            while( c != '\n' ) {
                recordLine += c ; 
                c = inputStream.get() ; 
            }
            cout << "Record found: "<< recordLine << "\n" ; 
        }
        else {
            cout << "Record not found." << "\n" ; 
        }
    }

    void deleteRecord( int id ) {
        // Append lines for the records whose
		// id does not equal the given id
		// in the list `lines`
        fstream inputStream ; 
		inputStream.open( filename , ios::in ) ;
		vector<string> lines ;
		while( !inputStream.eof() ) {
			string record ;
			inputStream >> record ;
			if( (int(record[0]) - 48) != id ) {
				lines.push_back( record ) ;
			}
		}
		inputStream.close() ;

        // reset hashtable
         for( int i = 0 ; i < tableSize ; i++ ) {
            hashTable[ i ] = -1 ; 
        } 

		// Clear all contents of the file (by opening it in ios::out mode)
		// and rewrite all files
        fstream outputStream ;
		outputStream.open( filename , ios::out ) ;
		for( int i = 0 ; i < lines.size() ; i++ ) {
            string record = lines[ i ] ; 
            int location = outputStream.tellp() ; 
            int index = hash( int(record[0]) - 48 ) ;
            hashTable[ index ] = location ; 
			outputStream.write( lines[i].c_str() , lines[i].length() ) ; 
            outputStream.write( "\n" , 1 ) ; 
		}
		outputStream.close() ;
    }

    void printTable() {
        for( int i = 0 ; i < tableSize ; i++ ) {
            cout << i << " : " << hashTable[ i ] << "\n" ; 
        }
    }

} ; 

int main() {
    DirectAccessFile file( "text.txt" , 10 ) ; 
    file.insertRecord( Employee( 3 , "Shubham" , 2 , 34 ) ) ;
    file.insertRecord( Employee( 4 , "kaustubh" , 3 , 35 ) ) ;
    file.printTable() ; 

    file.searchRecord( 3 ) ; 
    file.searchRecord( 1 ) ; 

    file.deleteRecord( 4 ) ; 
    file.printTable() ; 

    file.searchRecord( 4 ) ;

    return 0 ;
}