#include <string.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "mnemonic_table.cpp"

class Tokenizer {

    MnemonicTable mnemonicTable;

    public:

    std::vector<std::string> getTokens( std::string instruction ) {
        std::stringstream stream( instruction ) ; 
        std::string token;
        std::vector<std::string> tokens;
        while( stream >> token ) {
            tokens.push_back( token ) ; 
        }

        std::string label, mnemonic, operand1, operand2;
        if( mnemonicTable.isMnemonic( tokens[0] ) ) {
            mnemonic = tokens[0] ; 
            if( tokens.size() == 2 ) {
                operand1 = tokens[1] ; 
            }
            else if( tokens.size() == 3 ) {
                operand1 = tokens[1] ; 
                operand2 = tokens[2] ; 
            }
        }
        else if( mnemonicTable.isMnemonic( tokens[1] ) ) {
            label = tokens[0] ; 
            mnemonic = tokens[1] ; 
            if( tokens.size() == 3 ) {
                operand1 = tokens[2] ; 
            }
            else if( tokens.size() == 4 ) {
                operand1 = tokens[2] ; 
                operand2 = tokens[3] ; 
            }
        }

        return { label , mnemonic , operand1 , operand2 };
    }


} ;