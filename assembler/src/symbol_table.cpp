#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using std::vector, std::string, std::cout, std::pair, std::fstream, std::ios;

class SymbolTable {

    vector<pair<string,int>> symbols ; 
    public:

    SymbolTable() {
    }

    bool find( string& symbol_name ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                return true;
            }
        }
        return false;
    }

    int getSymbolIndex( string& symbol_name ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                return i+1;
            }
        }
        return -1; 
    }

    int getSymbolAddress( string& symbol_name ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                return symbols[i].second;
            }
        }
        return -1 ; 
    }

    int getSymbolAddressFromIndex( int index ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( i == (index-1) ) {
                return symbols[i].second ; 
            }
        }
    }

    void setSymbol( string& symbol_name , int address ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                symbols[i].second = address ; 
                return;
            }
        }
        symbols.push_back( { symbol_name , address } ) ; 
    }

    void print() {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            cout << (i+1) << " => " << symbols[i].first << " => " << symbols[i].second << "\n" ; 
        }
    }

    void saveTable( string filepath ) {
        fstream outputStream( filepath , ios::out ) ;
        outputStream << symbols.size() << " " ; 
        for( const pair<string,int>& literal : symbols ) {
            outputStream << literal.first << " " << literal.second << " " ; 
        }
        outputStream.close() ; 
    }

    void loadTable( string& filepath ) {
        symbols.clear() ; 
        fstream inputStream( filepath , ios::in ) ; 
        int size = 0 ; 
        inputStream >> size ; 
        for( int i = 0 ; i < size ; i++ ) {
            string name ; 
            int address ; 
            inputStream >> name >> address ; 
            symbols.push_back( { name , address } ) ;
        }
        inputStream.close() ;
    }

} ; 