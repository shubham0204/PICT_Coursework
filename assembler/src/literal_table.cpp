#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using std::vector, std::string, std::cout, std::pair, std::fstream, std::ios;

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
        return -1;
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

    void saveTable( string filepath ) {
        fstream outputStream( filepath , ios::out ) ;
        outputStream << literals.size() << " " ; 
        for( const pair<string,int>& literal : literals ) {
            outputStream << literal.first << " " << literal.second << " " ; 
        }
        outputStream.close() ; 
    }

    void loadTable( string& filepath ) {
        literals.clear() ; 
        fstream inputStream( filepath , ios::in ) ; 
        int size = 0 ; 
        inputStream >> size ; 
        for( int i = 0 ; i < size ; i++ ) {
            string name ; 
            int address ; 
            inputStream >> name >> address ; 
            literals.push_back( { name , address } ) ;
        }
        inputStream.close() ;
    }

} ; 