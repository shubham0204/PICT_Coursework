#include "tokenizer.cpp"
#include <fstream>
#include <iostream>

class Assembler {

    std::string sourceContents;
    std::vector<std::string> sourceLines;
    Tokenizer tokenizer;

    std::vector<std::string> getLines( std::string sourceContents ) {
        
    }

    public:

    Assembler( std::string sourceFilepath ) {
        std::fstream inputStream( sourceFilepath , std::ios::in ) ; 
        sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }

        sourceLines.clear() ; 
        std::stringstream ss( sourceContents );
        std::string line;
        while( std::getline( ss, line , '\n')) {
            sourceLines.push_back( line );
        }

        std::vector<std::vector<std::string>> tokens;
        for( std::string line : sourceLiness ) {
            tokens.push_back( tokenizer.getTokens( line ) ) ;
        }
    
    }

} ;

