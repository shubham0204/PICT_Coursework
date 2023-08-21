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
    fstream icOutputStream;
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
        icOutputStream = fstream( "../ic.txt" , ios::out ) ; 
        mnemonicTable = MnemonicTable() ; 
        symbolTable = SymbolTable() ; 
        literalTable = LiteralTable() ; 
    }

    void performPass1() {
        int locationCounter = 0 ; 
        literalTable.newPool() ; 
        for( int i = 0 ; i < instruction_tokens.size() ; i++ ) {
            vector<string> instruction = instruction_tokens[i] ; 
            string mnemonic_string = instruction[1] ;
            Mnemonic mnemonic = mnemonicTable.getMnemonic( mnemonic_string ) ; 

            if( mnemonic.mclass != MnemonicClass::DL && instruction[0] != "" ) {
                symbolTable.setSymbol( instruction[0] , locationCounter ) ;
            }

            if( mnemonic_string == "START" ) {
                locationCounter = stoi( instruction[2] ) ; 
                icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                << instruction[2] << ")" << "\n" ; 
            }
            if( mnemonic_string == "ORIGIN" ) {
                if( checkSymbolOffsetExpr( instruction[2] ) ) {
                    locationCounter = evaluateSymbolOffsetExpr( instruction[2] ) ;
                    icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else {
                    if( symbolTable.find( instruction[2] ) ) {
                        locationCounter = symbolTable.getSymbolAddress( instruction[2] ) ;
                        icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                        << instruction[2] << ")" << "\n" ; 
                    }
                    else {
                        locationCounter = stoi( instruction[2] ) ; 
                        icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
                        << locationCounter << ")" << "\n" ; 
                    }
                }
            }

            if( mnemonic_string == "LTORG" ) {
                literalTable.newPool() ; 
                literalTable.initializeLiterals( locationCounter ) ; 
                icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")" << "\n" ;
            }

            if( mnemonic_string == "EQU" ) {
                if( checkSymbolOffsetExpr( instruction[2] ) ) {
                    int address = evaluateSymbolOffsetExpr( instruction[2] ) ; 
                    symbolTable.setSymbol( instruction[0] , address ) ; 
                    icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                    << instruction[2] << ")" << "\n" ; 
                }
                else {
                    if( symbolTable.find( instruction[2] ) ) {
                        int address = symbolTable.getSymbolAddress( instruction[2] ) ;
                        symbolTable.setSymbol( instruction[0] , address ) ; 
                        icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "S , " 
                        << instruction[2] << ")" << "\n" ; 
                    }
                    else {
                        int address = stoi( instruction[2] ) ; 
                        symbolTable.setSymbol( instruction[0] , address ) ; 
                        icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")  (" << "C , " 
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
                    icOutputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << "S , " << symbolTable.getSymbolIndex(instruction[2]) << ")" << "\n" ; 
                }
                else if( mnemonic_string == "BC" ) {
                    if( !symbolTable.find( instruction[3] ) ) {
                        symbolTable.setSymbol( instruction[3] , -1 ) ;
                    }
                    icOutputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << conditionCodes[instruction[2]] << ")  " << "(" << "S , " << symbolTable.getSymbolIndex(instruction[3]) << ")" << "\n" ;
                }
                else if( mnemonic_string == "STOP" ) {
                    icOutputStream << "  (" << mnemonic.getClass() << " , " << mnemonic.opCode << ")" << "\n";
                }
                else {
                    if( instruction[3][0] == '=' ) {
                        // Insert literal
                        string literal = instruction[3].substr( 2 , instruction[3].find( '\'' ) ) ; 
                        literalTable.setLiteral( literal , -1 ) ;
                        icOutputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                        << mnemonic.opCode << ")  (" << registerCodes[instruction[2]] << ")  " << "(" << "L , " << literalTable.getLiteralIndex(literal) << ")" << "\n" ;
                    }
                    else {
                        // Insert symbol
                        if( !symbolTable.find( instruction[3] ) ) {
                            symbolTable.setSymbol( instruction[3] , -1 ) ;
                        }
                        icOutputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                        << mnemonic.opCode << ")  (" << registerCodes[instruction[2]] << ")  " << "(" << "S , " << symbolTable.getSymbolIndex(instruction[3]) << ")" << "\n" ;
                    }
                }
                locationCounter++ ; 
            }
            else if( mnemonic.mclass == MnemonicClass::DL ) {
                symbolTable.setSymbol( instruction[0] , locationCounter ) ;
                icOutputStream << locationCounter << "  (" << mnemonic.getClass() << " , " 
                    << mnemonic.opCode << ")  (" << "S , " << symbolTable.getSymbolIndex(instruction[0]) << ")  (C , " <<  instruction[2] << ")"  << "\n" ;
                if( instruction[1] == "DS" ) {
                    locationCounter += stoi( instruction[2] ) ;
                }
                else if( instruction[1] == "DC" ) {
                    locationCounter += 1 ;
                }
            }
        }
        
        icOutputStream.close() ; 

        printIC() ; 
        cout << "----------------Symbol Table ----------------- " << "\n" ; 
        symbolTable.print() ; 
        cout << "----------------Literal Table ----------------- " << "\n" ; 
        literalTable.print() ; 

        saveTables( symbolTable , literalTable ) ; 

    }

    bool checkSymbolOffsetExpr( string& symbolOffset ) {
        return (symbolOffset.find( "+" ) != string::npos) || (symbolOffset.find( "-" ) != string::npos) ; 
    }

    int evaluateSymbolOffsetExpr( string& symbolOffset ) {
        if( symbolOffset.find( "+" ) != string::npos ) {
            string symbolName = symbolOffset.substr( 0 , symbolOffset.find( "+" ) ) ;
            int offset = std::stoi( symbolOffset.substr( symbolOffset.find( "+" ) + 1 , symbolOffset.length() )) ; 
            int address = symbolTable.getSymbolAddress( symbolName ) + offset ; 
            return address ; 
        }
        else {
            string symbolName = symbolOffset.substr( 0 , symbolOffset.find( "-" ) ) ;
            int offset = std::stoi(symbolOffset.substr( symbolOffset.find( "-" ) + 1 , symbolOffset.length() )) ; 
            int address = symbolTable.getSymbolAddress( symbolName ) - offset ; 
            return address ; 
        }
    }

    void printIC() {
        fstream inputStream( "../ic.txt" , ios::in ) ; 
        string sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }
        cout << sourceContents << "\n" ; 
    }


    void saveTables( SymbolTable symbolTable , LiteralTable literalTable ) {
        fstream outputStream( "symbol_table.dat" , ios::app ) ;
        outputStream.write( (char*) &symbolTable , sizeof( symbolTable ) ) ;
        outputStream.close() ; 
        outputStream.open( "literal_table.dat" , ios::app ) ; 
        outputStream.write( (char*) &literalTable , sizeof( literalTable ) ) ;
        outputStream.close() ; 
    }

} ;

