#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class SymbolTable {

    std::vector<std::pair<std::string,int>> symbols ; 
    std::vector<std::string> symbol_values;

    public:

    SymbolTable() {
    }

    bool find( std::string& symbol_name ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                return true;
            }
        }
        return false;
    }

    int getSymbolIndex( std::string& symbol_name ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                return i+1;
            }
        }
        return -1 ; 
    }

    int getSymbolAddress( std::string& symbol_name ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                return symbols[i].second;
            }
        }
        return -1 ; 
    }

    void setSymbol( std::string& symbol_name , int address ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                symbols[i].second = address ; 
                return;
            }
        }
        symbols.push_back( { symbol_name , address } ) ; 
    }

    void setSymbolValue( std::string& symbol_name , std::string value ) {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            if( symbols[i].first == symbol_name ) {
                //symbols[i].second = address ; 
                break;
            }
        }
    }

    void print() {
        for( int i = 0 ; i < symbols.size() ; i++ ) {
            std::cout << (i+1) << " => " << symbols[i].first << " => " << symbols[i].second << "\n" ; 
        }
    }

} ; 