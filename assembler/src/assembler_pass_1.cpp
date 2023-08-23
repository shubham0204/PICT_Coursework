#include "tokenizer.cpp"
#include "symbol_table.cpp"
#include "literal_table.cpp"
#include <fstream>
#include <iostream>
using std::fstream, std::ios;

#define LBR '\n'

class AssemblerPass1 {

    unordered_map<string,int> conditionCodes = {
        { "LT",1 },
        { "LE",2 },
        { "EQ",3 } ,
        { "GT",4 } ,
        { "GE",5 },
        { "ANY",6 }
    } ;
    unordered_map<string,int> registerCodes = {
        { "AREG",1 },
        { "BREG",2 },
        { "CREG",3 } ,
        { "DREG",4 }
    } ;


    vector<vector<string>> instruction_tokens;
    fstream icOutputStream;
    SymbolTable symbolTable;
    Tokenizer tokenizer;
    MnemonicTable mnemonicTable;
    LiteralTable literalTable;

    string symbolTableFilepath ; 
    string literalTableFilepath ; 
    string icFilepath;

    public:

    AssemblerPass1( 
        string sourceFilepath , 
        string icFilepath,
        string symbolTableFilepath,
        string literalTableFilepath
        ) {

        this -> icFilepath = icFilepath ; 
        this -> symbolTableFilepath = symbolTableFilepath ; 
        this -> literalTableFilepath = literalTableFilepath ;   

        string sourceContents = readTextFile( sourceFilepath ) ;
        vector<string> lines = readLines( sourceContents ) ; 
        for( string line : lines ) {
            instruction_tokens.push_back( tokenizer.getTokens( line ) );
        }
        icOutputStream = fstream( icFilepath ,ios::out ) ; 
        mnemonicTable = MnemonicTable() ; 
        symbolTable = SymbolTable() ; 
        literalTable = LiteralTable() ; 
    }

    void performPass() {
        int locationCounter = 0 ; 
        literalTable.newPool() ; 
        for( int i = 0 ; i < instruction_tokens.size() ; i++ ) {
            vector<string> instruction = instruction_tokens[i] ; 
            string mnemonic_string = instruction[1] ;
            Mnemonic mnemonic = mnemonicTable.getMnemonic( mnemonic_string ) ; 

            if( mnemonic.mclass != MnemonicClass::DL && instruction[0] != "" ) {
                symbolTable.setSymbol( instruction[0],locationCounter ) ;
            }

            if( mnemonic_string == "START" ) {
                locationCounter = stoi( instruction[2] ) ; 
                icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "C," 
                << instruction[2] << ")" << LBR ; 
            }
            if( mnemonic_string == "ORIGIN" ) {
                if( checkSymbolOffsetExpr( instruction[2] ) ) {
                    string symbol = "" ; 
                    locationCounter = evaluateSymbolOffsetExpr( instruction[2],symbol ) ;
                    icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "S," 
                    << symbolTable.getSymbolIndex( symbol ) << ")" << LBR ; 
                }
                else {
                    if( symbolTable.find( instruction[2] ) ) {
                        locationCounter = symbolTable.getSymbolAddress( instruction[2] ) ;
                        icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "S," 
                        << instruction[2] << ")" << LBR ; 
                    }
                    else {
                        locationCounter = stoi( instruction[2] ) ; 
                        icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "C," 
                        << locationCounter << ")" << LBR ; 
                    }
                }
            }

            if( mnemonic_string == "LTORG" ) {
                literalTable.newPool() ; 
                literalTable.initializeLiterals( locationCounter ) ; 
                icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ")" << LBR ;
            }

            if( mnemonic_string == "EQU" ) {
                if( checkSymbolOffsetExpr( instruction[2] ) ) {
                    string symbol = "" ; 
                    int address = evaluateSymbolOffsetExpr( instruction[2],symbol ) ; 
                    symbolTable.setSymbol( instruction[0],address ) ; 
                    icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "S," 
                    << symbolTable.getSymbolIndex( symbol ) << ")" << LBR ; 
                }
                else {
                    if( symbolTable.find( instruction[2] ) ) {
                        int address = symbolTable.getSymbolAddress( instruction[2] ) ;
                        symbolTable.setSymbol( instruction[0],address ) ; 
                        icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "S," 
                        << symbolTable.getSymbolIndex( instruction[2] ) << ")" << LBR ; 
                    }
                    else {
                        int address = stoi( instruction[2] ) ; 
                        symbolTable.setSymbol( instruction[0],address ) ; 
                        icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ") (" << "C," 
                        << locationCounter << ")" << LBR ; 
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
                        symbolTable.setSymbol( instruction[2],-1 ) ;
                    }
                    icOutputStream << locationCounter << " (" << mnemonic.getClass() << "," 
                    << mnemonic.opCode << ") (" << "S," << symbolTable.getSymbolIndex(instruction[2]) << ")" << LBR ; 
                }
                else if( mnemonic_string == "BC" ) {
                    if( !symbolTable.find( instruction[3] ) ) {
                        symbolTable.setSymbol( instruction[3],-1 ) ;
                    }
                    icOutputStream << locationCounter << " (" << mnemonic.getClass() << "," 
                    << mnemonic.opCode << ") (" << conditionCodes[instruction[2]] << ") (" << "S," << symbolTable.getSymbolIndex(instruction[3]) << ")" << LBR ;
                }
                else if( mnemonic_string == "STOP" ) {
                    icOutputStream << " (" << mnemonic.getClass() << "," << mnemonic.opCode << ")" << LBR;
                }
                else {
                    if( instruction[3][0] == '=' ) {
                        // Insert literal
                        string literal = instruction[3].substr( 2,instruction[3].find( '\'' ) ) ; 
                        literalTable.setLiteral( literal,-1 ) ;
                        icOutputStream << locationCounter << " (" << mnemonic.getClass() << "," 
                        << mnemonic.opCode << ") (" << registerCodes[instruction[2]] << ") (" << "L," << literalTable.getLiteralIndex(literal) << ")" << LBR ;
                    }
                    else {
                        // Insert symbol
                        if( !symbolTable.find( instruction[3] ) ) {
                            symbolTable.setSymbol( instruction[3],-1 ) ;
                        }
                        icOutputStream << locationCounter << " (" << mnemonic.getClass() << "," 
                        << mnemonic.opCode << ") (" << registerCodes[instruction[2]] << ") (" << "S," << symbolTable.getSymbolIndex(instruction[3]) << ")" << LBR ;
                    }
                }
                locationCounter++ ; 
            }
            else if( mnemonic.mclass == MnemonicClass::DL ) {
                symbolTable.setSymbol( instruction[0],locationCounter ) ;
                string constantVal = instruction[2] ; 
                // TODO: Remove quotes from constantVal 
                icOutputStream << locationCounter << " (" << mnemonic.getClass() << "," 
                    << mnemonic.opCode << ") (" << "S," << symbolTable.getSymbolIndex(instruction[0]) << ") (C," << constantVal << ")"  << LBR ;
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
        cout << "----------------Symbol Table ----------------- " << LBR ; 
        symbolTable.print() ; 
        cout << "----------------Literal Table ----------------- " << LBR ; 
        literalTable.print() ; 

        saveTables( symbolTable,literalTable ) ; 

    }

    bool checkSymbolOffsetExpr( string& symbolOffset ) {
        return (symbolOffset.find( "+" ) != string::npos) || (symbolOffset.find( "-" ) != string::npos) ; 
    }

    int evaluateSymbolOffsetExpr( string& symbolOffset,string& symbolName ) {
        if( symbolOffset.find( "+" ) != string::npos ) {
            symbolName = symbolOffset.substr( 0,symbolOffset.find( "+" ) ) ;
            int offset = std::stoi( symbolOffset.substr( symbolOffset.find( "+" ) + 1,symbolOffset.length() )) ; 
            int address = symbolTable.getSymbolAddress( symbolName ) + offset ; 
            return address ; 
        }
        else {
            symbolName = symbolOffset.substr( 0,symbolOffset.find( "-" ) ) ;
            int offset = std::stoi(symbolOffset.substr( symbolOffset.find( "-" ) + 1,symbolOffset.length() )) ; 
            int address = symbolTable.getSymbolAddress( symbolName ) - offset ; 
            return address ; 
        }
    }

    void printIC() {
        string sourceContents = readTextFile( icFilepath ) ;
        cout << sourceContents << LBR ; 
    }

    static string readTextFile( string filepath ) {
        fstream inputStream( filepath,ios::in ) ; 
        string sourceContents = "" ;
        char c = inputStream.get() ; 
        while( !inputStream.eof() ) {
            sourceContents += c;
            c = inputStream.get();  
        }
        return sourceContents ;
    }

    static vector<string> readLines( string sourceContents ) {
        vector<string> lines;
        stringstream ss( sourceContents );
        string line;
        while( getline( ss, line,'\n')) {
            lines.push_back( line );
        }
        return lines;
    }


    void saveTables( SymbolTable symbolTable,LiteralTable literalTable ) {
        symbolTable.saveTable( symbolTableFilepath ) ; 
        literalTable.saveTable( literalTableFilepath ) ;
    }
} ;

