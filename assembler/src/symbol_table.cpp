#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using std::vector, std::string, std::cout, std::pair;

class SymbolTable {

    vector<pair<string,int>> symbols ; 
    vector<string> symbol_values;

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

    void setSymbolValue( string& symbol_name , string value ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                //symbols[i].second = address ; 
                break;
            }
        }
    }

    void print() {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            cout << (i+1) << " => " << symbols[i].first << " => " << symbols[i].second << "\n" ; 
        }
    }

} ; 