#include <iostream>
using namespace std ; 

class Record {

    string name = "----"; 
    string telephone = "----" ; 

    bool isEmpty() {
        return name == "----" ; 
    }

    public:

    friend class HashTable ; 

} ; 

class HashTable {

    int tableSize = 0 ;
    Record* records = nullptr ; 

 
    public:

    HashTable( int size ) {
        tableSize = size ; 
        records = new Record[ tableSize ] ; 
    }

    int hash( string telephone ) {
        return (int( telephone[9] ) - 30) % tableSize ; 
    }


    void insertWithoutReplacement( string name , string phone ) {
        int hashAddress = hash( phone ) ; 
        if( records[ hashAddress ].isEmpty() ) {
            Record record ; 
            record.name = name ; 
            record.telephone = phone ; 
            records[ hashAddress ] = record ; 
        }
        else {
            int currIndex = hashAddress ; 
            int numPasses = 0 ; 
            while( !records[ currIndex % tableSize ].isEmpty() && numPasses < tableSize ) {
                currIndex += 1 ; 
                numPasses += 1; 
            }
            Record record ; 
            record.name = name ; 
            record.telephone = phone ; 
            records[ currIndex ] = record ;
        }
    }

    void insertWithReplacement( string name , string phone ) {
        int hashAddress = hash( phone ) ; 
        if( records[ hashAddress ].isEmpty() ) {
            Record record ; 
            record.name = name ; 
            record.telephone = phone ; 
            records[ hashAddress ] = record ;
        }
        else {
            if( hash( records[ hashAddress ].telephone ) == hashAddress ) {
                // Next empty
                int currIndex = hashAddress ; 
                int numPasses = 0 ; 
                while( !records[ currIndex % tableSize ].isEmpty() && numPasses < tableSize ) {
                    currIndex += 1 ; 
                    numPasses += 1; 
                }
                Record record ; 
                record.name = name ; 
                record.telephone = phone ; 
                records[ currIndex ] = record ;
            }
            else {
                Record moveRecord = records[ hashAddress ] ;
                Record record ; 
                record.name = name ; 
                record.telephone = phone ; 
                records[ hashAddress ] = record ;
                int currIndex = hashAddress ; 
                int numPasses = 0 ; 
                while( !records[ currIndex % tableSize ].isEmpty() && numPasses < tableSize ) {
                    currIndex += 1 ; 
                    numPasses += 1; 
                }
                records[ currIndex ] = moveRecord ;
            }
        }
    }

    void print() {
        cout << "--------------------------------------" << "\n" ; 
        for( int i = 0 ; i < tableSize ; i++ ) {
            cout << records[i].name << "   " << records[i].telephone << "\n" ;
        }
        cout << "--------------------------------------" << "\n" ; 
    }

    int search( string phone ) {
        int hashAddress = hash( phone ) ;
        int numComparisons = 1 ; 
        cout << hashAddress << "\n" ; 
        if( records[ hashAddress ].telephone == phone ) {
            cout << "Record Found!" << "\n" ; 
            cout << "Name is " << records[ hashAddress ].name << "\n" ; 
        }
        else {
            int currIndex = hashAddress ; 
            int numPasses = 0 ; 
            while( numPasses < tableSize ) {
                if( records[ currIndex ].telephone == phone ) {
                    cout << "Record Found!" << "\n" ; 
                    cout << "Name is " << records[ currIndex ].name << "\n" ; 
                    break ; 
                }
                currIndex = ( currIndex + 1 ) % tableSize ; 
                numComparisons += 1 ; 
                numPasses += 1 ; 
            }
        }
        return numComparisons ; 
    }

} ; 

int main() {
    HashTable table( 10 ) ; 
    table.insertWithoutReplacement( "name1" , "helloworld" )  ;
    table.print() ; 
    table.insertWithoutReplacement( "name2" , "helloworle" )  ;
    table.print() ; 
    table.insertWithoutReplacement( "name3" , "helloworlf" )  ;
    table.print() ; 
    table.insertWithoutReplacement( "name4" , "helloworlg" )  ;
    table.print() ;
    table.insertWithoutReplacement( "name5" , "helloworln" )  ;
    table.print() ;
    table.insertWithoutReplacement( "name6" , "helloworlo" )  ;
    table.print() ;
    table.insertWithoutReplacement( "name7" , "helloworlp" )  ;
    table.print() ;

    HashTable table2( 10 ) ; 
    table2.insertWithReplacement( "name1" , "helloworld" )  ;
    table2.print() ; 
    table2.insertWithReplacement( "name2" , "helloworle" )  ;
    table2.print() ; 
    table2.insertWithReplacement( "name3" , "helloworlf" )  ;
    table2.print() ; 
    table2.insertWithReplacement( "name4" , "helloworlg" )  ;
    table2.print() ;
    table2.insertWithReplacement( "name5" , "helloworln" )  ;
    table2.print() ;
    table2.insertWithReplacement( "name6" , "helloworlo" )  ;
    table2.print() ;
    table2.insertWithReplacement( "name7" , "helloworlp" )  ;
    table2.print() ;
    table2.insertWithReplacement( "name8" , "helloworlh" )  ;
    table2.print() ;

    table2.search( "helloworln" ) ; 

    return 0;
}