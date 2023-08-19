#include "tokenizer.cpp"
#include "symbol_table.cpp"
#include "literal_table.cpp"
#include <fstream>
#include <iostream>
using std::fstream, std::ios;

class Assembler {

    unordered_map<string,int> conditionCodes = {
        { "LT" , 1 } , 
        { "LE" , 2 } , 
        { "EQ" , 3 } ,
        { "GT" , 4 } ,
        { "GE" , 5 } , 
        { "ANY" , 6 }
    } ;
    unordered_map<string,int> registerCodes = {
        { "AREG" , 1 } , 
        { "BREG" , 2 } , 
        { "CREG" , 3 } ,
        { "DREG" , 4 }
    } ;


    vector<vector<string>> instruction_tokens;
    fstream outputStream;
    SymbolTable symbolTable;
    Tokenizer tokenizer;
    MnemonicTable mnemonicTable;
    LiteralTable literalTable;

    vector<string> getLines( string sourceFilepath ) {
        fstream inputStream( sourceFilepath , ios::in ) ; 
        string sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }
        vector<string> lines;
        stringstream ss( sourceContents );
        string line;
        while( getline( ss, line , '\n')) {
            lines.push_back( line );
        }
        return lines;
    }

    public:

    Assembler( string sourceFilepath ) {
        vector<string> lines = getLines( sourceFilepath ) ; 
        for( string line : lines ) {
            instruction_tokens.push_back( tokenizer.getTokens( line ) );
        }
        outputStream = fstream( "../ic.txt" , ios::out ) ; 
        mnemonicTable = MnemonicTable() ; 
        symbolTable = SymbolTable() ; 
        literalTable = LiteralTable() ; 
    }

    void performPass1() {
        int locationCounter = 0 ; 
        literalTable.newPool() ; 
        for( int i = 0 ; i < instruction_tokens.size() ; i++ ) {
            vector<string> instruction = instruction_tokens[i] ; 
            //cout << "Instruction: " << instruction[1] << "\n" ; 
            string mnemonic_string = instruction[1] ;
            Mnemonic mnemonic = mnemonicTable.getMnemonic( mnemonic_string ) ; 

            if( mnemonic.mclass != MnemonicClass::DL && instruction[0] != "" ) {
                symbolTable.setSymbol( instruction[0] , locationCounter ) ;
            }

            if( mnemonic_string == "START" ) {
                locationCounter = stoi( instruction[2] ) ; 
                outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                << instruction[2] << ")" << "\n" ; 
            }
            if( mnemonic_string == "ORIGIN" ) {
                if( instruction[2].find( "+" ) != string::npos ) {
                    string symbolName = instruction[2].substr( 0 , instruction[2].find( "+" ) ) ;
                    int offset = stoi(instruction[2].substr( instruction[2].find( "+" ) + 1 , instruction[2].length() )) ; 
                    locationCounter = symbolTable.getSymbolAddress( symbolName ) + offset ; 
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else if( instruction[2].find( "-" ) != string::npos ) {
                    string symbolName = instruction[2].substr( 0 , instruction[2].find( "-" ) ) ;
                    int offset = stoi(instruction[2].substr( instruction[2].find( "-" ) + 1 , instruction[2].length() )) ; 
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
                        locationCounter = stoi( instruction[2] ) ; 
                        outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                        << locationCounter << ")" << "\n" ; 
                    }
                }
            }

            if( mnemonic_string == "LTORG" ) {
                literalTable.newPool() ; 
                literalTable.initializeLiterals( locationCounter ) ; 
                outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")" << "\n" ;
            }

            if( mnemonic_string == "EQU" ) {
                if( instruction[2].find( "+" ) != string::npos ) {
                    string symbolName = instruction[2].substr( 0 , instruction[2].find( "+" ) ) ;
                    int offset = stoi(instruction[2].substr( instruction[2].find( "+" ) + 1 , instruction[2].length() )) ; 
                    int address = symbolTable.getSymbolAddress( symbolName ) + offset ; 
                    symbolTable.setSymbol( instruction[0] , address ) ; 
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else if( instruction[2].find( "-" ) != string::npos ) {
                    string symbolName = instruction[2].substr( 0 , instruction[2].find( "-" ) ) ;
                    int offset = stoi(instruction[2].substr( instruction[2].find( "-" ) + 1 , instruction[2].length() )) ; 
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
                        int address = stoi( instruction[2] ) ; 
                        symbolTable.setSymbol( instruction[0] , address ) ; 
                        outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                        << locationCounter << ")" << "\n" ; 
                    }
                }
            }

            if( mnemonic_string == "END" ) {
                literalTable.initializeLiterals( locationCounter ) ; 
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
                    if( !symbolTable.find( instruction[3] ) ) {
                        symbolTable.setSymbol( instruction[3] , -1 ) ;
                    }
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << conditionCodes[instruction[2]] << ")  " << "(" << "S , " << symbolTable.getSymbolIndex(instruction[3]) << ")" << "\n" ;
                }
                else if( mnemonic_string == "STOP" ) {
                    outputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")" << "\n";
                }
                else {
                    if( instruction[3][0] == '=' ) {
                        // Insert literal
                        string literal = instruction[3].substr( 2 , instruction[3].find( '\'' ) ) ; 
                        // cout << literal << "\n" ; 
                        literalTable.setLiteral( literal , -1 ) ;
                        outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                        << mnemonic.opCode << ")  (" << registerCodes[instruction[2]] << ")  " << "(" << "L , " << literalTable.getLiteralIndex(literal) << ")" << "\n" ;
                    }
                    else {
                        // Insert symbol
                        if( !symbolTable.find( instruction[3] ) ) {
                            symbolTable.setSymbol( instruction[3] , -1 ) ;
                        }
                        outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                        << mnemonic.opCode << ")  (" << registerCodes[instruction[2]] << ")  " << "(" << "S , " << symbolTable.getSymbolIndex(instruction[3]) << ")" << "\n" ;
                    }
                }
                locationCounter++ ; 
            }
            else if( mnemonic.mclass == MnemonicClass::DL ) {
                if( instruction[1] == "DS" ) {
                    symbolTable.setSymbol( instruction[0] , locationCounter ) ;
                    outputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << "S , " << symbolTable.getSymbolIndex(instruction[0]) << ")  (C , " <<  instruction[2] << ")"  << "\n" ;
                    locationCounter += stoi( instruction[2] ) ;
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

        fstream inputStream( "../ic.txt" , ios::in ) ; 
        string sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }
        cout << sourceContents << "\n" ; 

        cout << "----------------Symbol Table ----------------- " << "\n" ; 
        symbolTable.print() ; 
        cout << "----------------Literal Table ----------------- " << "\n" ; 
        literalTable.print() ; 
    }

} ;

