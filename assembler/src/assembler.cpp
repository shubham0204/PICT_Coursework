#include "tokenizer.cpp"
#include "symbol_table.cpp"
#include <fstream>
#include <iostream>

class Assembler {

    std::unordered_map<std::string,int> conditionCodes = {
        { "LT" , 1 } , 
        { "LE" , 2 } , 
        { "EQ" , 3 } ,
        { "GT" , 4 } ,
        { "GE" , 5 } , 
        { "ANY" , 6 }
    } ;
    std::unordered_map<std::string,int> registerCodes = {
        { "AREG" , 1 } , 
        { "BREG" , 2 } , 
        { "CREG" , 3 } ,
        { "DREG" , 4 }
    } ;


    std::vector<std::vector<std::string>> instruction_tokens;
    std::fstream outputStream;
    SymbolTable symbolTable;
    Tokenizer tokenizer;
    MnemonicTable mnemonicTable;

    std::vector<std::string> getLines( std::string sourceFilepath ) {
        std::fstream inputStream( sourceFilepath , std::ios::in ) ; 
        std::string sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }
        std::vector<std::string> lines;
        std::stringstream ss( sourceContents );
        std::string line;
        while( std::getline( ss, line , '\n')) {
            lines.push_back( line );
        }
        return lines;
    }

    public:

    Assembler( std::string sourceFilepath ) {
        std::vector<std::string> lines = getLines( sourceFilepath ) ; 
        for( std::string line : lines ) {
            instruction_tokens.push_back( tokenizer.getTokens( line ) );
        }
        outputStream = std::fstream( "../ic.txt" , std::ios::out ) ; 
        mnemonicTable = MnemonicTable() ; 
        symbolTable = SymbolTable() ; 
    }

    void performPass1() {
        int locationCounter = 0 ; 
        for( int i = 0 ; i < instruction_tokens.size() ; i++ ) {
            std::vector<std::string> instruction = instruction_tokens[i] ; 
            std::cout << "Instruction: " << instruction[1] << "\n" ; 
            std::string mnemonic_string = instruction[1] ;
            Mnemonic mnemonic = mnemonicTable.getMnemonic( mnemonic_string ) ; 

            if( mnemonic.mclass != MnemonicClass::DL && instruction[0] != "" ) {
                symbolTable.setSymbol( instruction[0] , locationCounter ) ;
            }

            if( mnemonic_string == "START" ) {
                locationCounter = std::stoi( instruction[2] ) ; 
                outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                << instruction[2] << ")" << "\n" ; 
            }
            if( mnemonic_string == "ORIGIN" ) {
                if( instruction[2].find( "+" ) != std::string::npos ) {
                    std::string symbolName = instruction[2].substr( 0 , instruction[2].find( "+" ) ) ;
                    int offset = std::stoi(instruction[2].substr( instruction[2].find( "+" ) + 1 , instruction[2].length() )) ; 
                    locationCounter = symbolTable.getSymbolAddress( symbolName ) + offset ; 
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else if( instruction[2].find( "-" ) != std::string::npos ) {
                    std::string symbolName = instruction[2].substr( 0 , instruction[2].find( "-" ) ) ;
                    int offset = std::stoi(instruction[2].substr( instruction[2].find( "-" ) + 1 , instruction[2].length() )) ; 
                    locationCounter = symbolTable.getSymbolAddress( symbolName ) - offset ; 
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else {
                    if( symbolTable.find( instruction[2] ) ) {
                        locationCounter = symbolTable.getSymbolAddress( instruction[2] ) ;
                        outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                        << instruction[2] << ")" << "\n" ; 
                    }
                    else {
                        locationCounter = std::stoi( instruction[2] ) ; 
                        outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                        << locationCounter << ")" << "\n" ; 
                    }
                }
            }

            if( mnemonic_string == "EQU" ) {
                if( instruction[2].find( "+" ) != std::string::npos ) {
                    std::string symbolName = instruction[2].substr( 0 , instruction[2].find( "+" ) ) ;
                    int offset = std::stoi(instruction[2].substr( instruction[2].find( "+" ) + 1 , instruction[2].length() )) ; 
                    int address = symbolTable.getSymbolAddress( symbolName ) + offset ; 
                    symbolTable.setSymbol( instruction[0] , address ) ; 
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else if( instruction[2].find( "-" ) != std::string::npos ) {
                    std::string symbolName = instruction[2].substr( 0 , instruction[2].find( "-" ) ) ;
                    int offset = std::stoi(instruction[2].substr( instruction[2].find( "-" ) + 1 , instruction[2].length() )) ; 
                    int address = symbolTable.getSymbolAddress( symbolName ) - offset ; 
                    symbolTable.setSymbol( instruction[0] , address ) ; 
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else {
                    if( symbolTable.find( instruction[2] ) ) {
                        int address = symbolTable.getSymbolAddress( instruction[2] ) ;
                        symbolTable.setSymbol( instruction[0] , address ) ; 
                        outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                        << instruction[2] << ")" << "\n" ; 
                    }
                    else {
                        int address = std::stoi( instruction[2] ) ; 
                        symbolTable.setSymbol( instruction[0] , address ) ; 
                        outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                        << locationCounter << ")" << "\n" ; 
                    }
                }
            }

            if( mnemonic_string == "END" ) {
                break;
            }

            if( mnemonic.mclass == MnemonicClass::IS ) {
                if( mnemonic_string == "READ" || mnemonic_string == "PRINT" ) {
                    if( !symbolTable.find( instruction[2] ) ) {
                        symbolTable.setSymbol( instruction[2] , -1 ) ;
                    }
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << "S , " << symbolTable.getSymbolIndex(instruction[2]) << ")" << "\n" ; 
                }
                else if( mnemonic_string == "BC" ) {
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << conditionCodes[instruction[2]] << ")  " << "(" << "S , " << symbolTable.getSymbolIndex(instruction[3]) << ")" << "\n" ;
                }
                else if( mnemonic_string == "STOP" ) {
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")" << "\n";
                }
                else {
                    if( !symbolTable.find( instruction[3] ) ) {
                        symbolTable.setSymbol( instruction[3] , -1 ) ;
                    }
                    
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << registerCodes[instruction[2]] << ")  " << "(" << "S , " << symbolTable.getSymbolIndex(instruction[3]) << ")" << "\n" ;
                }
                locationCounter++ ; 
            }
            else if( mnemonic.mclass == MnemonicClass::DL ) {
                if( instruction[1] == "DS" ) {
                    symbolTable.setSymbol( instruction[0] , locationCounter ) ;
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << "S , " << symbolTable.getSymbolIndex(instruction[0]) << ")  (C , " <<  instruction[2] << ")"  << "\n" ;
                    locationCounter += std::stoi( instruction[2] ) ;
                }
                else if( instruction[1] == "DC" ) {
                    symbolTable.setSymbol( instruction[0] , locationCounter ) ;
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << "S , " << symbolTable.getSymbolIndex(instruction[0]) << ")  (C , " <<  instruction[2] << ")"  << "\n" ;
                    locationCounter += 1 ;
                }
            }

        }
        outputStream.close() ; 
        symbolTable.print() ; 
    }

} ;

