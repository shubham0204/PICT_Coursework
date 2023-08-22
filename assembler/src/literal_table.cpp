#include <vector>
#include <string>
#include <iostream>
using std::vector, std::string, std::cout, std::pair;

class LiteralTable {

    vector<pair<string,int>> literals;
    int litTabPtr = 0 ;
    vector<int> poolIndices ; 
    int searchIndex = 0; 

    public:

    LiteralTable() {
    }

    bool find( string& literalName ) {
        for( int i = 0 ; i < literals.size() ; i++ ) {
            if( literals[i].first == literalName ) {
                return true;
            }
        }
        return false;
    }

    int getLiteralIndex( string& literalName ) {
        for( int i = searchIndex ; i < literals.size() ; i++ ) {
            if( literals[i].first == literalName ) {
                return i+1;
            }
        }
        return -1 ; 
    }

    int getLiteralAddress( string& literalName ) {
        for( int i = 0 ; i < literals.size() ; i++ ) {
            if( literals[i].first == literalName ) {
                return literals[i].second;
            }
        }
        return -1 ; 
    }

    void newPool() {
        searchIndex = poolIndices.size() ; 
        poolIndices.push_back( litTabPtr ) ; 
    }

    int getLiteralAddressFromIndex( int index ) {
        for( int i = 0 ; i < literals.size() ; i++ ) {
            if( i == (index-1) ) {
                return literals[i].second ; 
            }
        }
    }

    void setLiteral( string& literalName , int address ) {
        for( int i = searchIndex + 1 ; i < literals.size() ; i++ ) {
            if( literals[i].first == literalName ) {
                literals[i].second = address ; 
                return;
            }
        }
        literals.push_back( { literalName , address } ) ; 
        litTabPtr++ ; 
    }

    void initializeLiterals( int& locationCounter ) { 
        for( int i = 0 ; i < literals.size() ; i++ ) {
            if( literals[i].second == -1 ) {
                literals[i].second = locationCounter ; 
                locationCounter++ ; 
            }
        }
    }

    void print() {
        for( int i = 0 ; i < literals.size() ; i++ ) {
            cout << (i+1) << " => " << literals[i].first << " => " << literals[i].second << "\n" ; 
        }
        cout << "----------------Pool Table ----------------- " << "\n" ; 
        for( int i = 0 ; i < poolIndices.size() ; i++ ) {
            cout << "Pool #" << (i+1) << " => index in literal table => " << poolIndices[i] << "\n" ; 
        }
    }

} ; 