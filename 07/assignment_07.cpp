#include <iostream>
#include <fstream>
#include <ios>
using namespace std ;

class FileManager {

private:
    string filename ;
    fstream inputStream ;
    fstream outputStream ;
    int maxCharsInText ;

public:

    FileManager( string filename ) {
        this -> filename = filename ;
        cout << "Enter number of characters in data: " ; cin >> maxCharsInText ;
    }

    void printData() {
        inputStream.open( filename , ios::in ) ;
        char text[ maxCharsInText ] ;
        while( inputStream.read( &text[0] , sizeof( text ) ) ) {
            cout << text ;
        }
        cout << "\n" ;
        inputStream.close() ;
    }

    void newData() {
        char text[ maxCharsInText ] ;
        cin.getline( &text[0] , sizeof( text ) , 'x' ) ;
        outputStream.open( filename , ios::out ) ;
        outputStream.write( &text[0] , sizeof( text ) ) ;
        outputStream.close() ;
    }

    void appendData() {
        char text[ maxCharsInText ] ;
        cin.getline( &text[0] , sizeof( text ) , 'x' ) ;
        outputStream.open( filename , ios::app ) ;
        outputStream.write( &text[0] , sizeof( text ) ) ;
        outputStream.close() ;
    }


    void insert() {
        char text[ 10 ] ;
        cin.getline( &text[0] , sizeof( text ) , 'x' ) ;
        outputStream.open( filename , ios::out ) ;
        outputStream.seekp( 5 ) ;
        outputStream.write( "Ja" , 2 ) ;
        outputStream.close() ;
    }

};


int main() {

    FileManager manager( "file.txt" ) ;

    while( true ) {
        int option ;
        cout << "Enter option: " << "\n" ;
        cout << "1 -> Print data" << "\n" ;
        cout << "2 -> Enter new data" << "\n" ;
        cout << "3 -> Append data" << "\n" ;
        cin >> option ;
        if( option == 1 ) {
            manager.printData() ;
        }
        else if( option == 2 ) {
            manager.newData() ;
        }
        else if( option == 3 ) {
            manager.appendData() ;
        }
        else if( option == 4 ) {
            manager.insert() ;
        }
        else {
            break;
        }
    }

    return 0 ;
}