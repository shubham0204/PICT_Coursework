#include "assembler_pass_1.cpp"

#define LBR '\n'

class AssemblerPass2 {

    vector<string> icLines ; 
    vector<vector<string>> icTokens ; 

    SymbolTable symbolTable ; 
    LiteralTable literalTable ; 

public:

    AssemblerPass2() {
        cout << "Read IC" << LBR ; 
        pair<SymbolTable,LiteralTable> tables = loadTables() ;
        symbolTable = tables.first ; 
        literalTable = tables.second ;  
        
        string icContent = AssemblerPass1::readTextFile( "ic.txt" ) ; 
        icLines = AssemblerPass1::readLines( icContent ) ;

        for( const string& line : icLines ) {
            icTokens.push_back( Tokenizer::splitBySpace( line ) ) ;
        }

        for( const vector<string>& tokens : icTokens ) {
            if( tokens.size() == 4 ) {
                cout << tokens[1] << LBR ; 
                for( const string& item : parseStringTuple( tokens[2] ) ) {
                    cout << item << " " ;
                }
                cout << LBR ; 
            }
        }
    }

    void performPass() {
        for( const vector<string>& lineTokens : icTokens ) {
            int tokensSize = lineTokens.size() ; 

            if( tokensSize == 4 ) {
                string locationCounter = lineTokens[0] ;
                string operand1 = parseStringTuple( lineTokens[1] )[1] ; 

                int operand2 = 0 ; 
                vector<string> operand2Tuple = parseStringTuple( lineTokens[2] ) ;
                if( operand2Tuple.size() == 2 ) {
                    if( operand2Tuple[0] == "S" ) {
                        int index = std::stoi( operand2Tuple[1] ) ;
                        operand2 = symbolTable.getSymbolAddressFromIndex( index ) ;
                    }
                }
                else {
                    operand2 = std::stoi( operand2Tuple[0] ) ;
                }

                int operand3 = 0 ; 
                vector<string> operand3Tuple = parseStringTuple( lineTokens[3] ) ;
                if( operand3Tuple[0] == "S" ) {
                    int index = std::stoi( operand3Tuple[1] ) ;
                    operand3 = symbolTable.getSymbolAddressFromIndex( index ) ;
                }
                else if( operand3Tuple[0] == "L" ) {
                    int index = std::stoi( operand3Tuple[1] ) ;
                    operand3 = literalTable.getLiteralAddressFromIndex( index ) ;
                }
                else if( operand3Tuple[0] == "C" ) {
                    operand3 = std::stoi( operand3Tuple[1] ) ;
                }

                cout << locationCounter << " " << operand1 << " " << operand2 << " " << operand3 << LBR ; 
            }
            else if ( tokensSize == 2 ) {
                /*
                string operand1 = parseStringTuple( lineTokens[1] )[1] ; 
                int operand2 = 0 ; 
                vector<string> operand2Tuple = parseStringTuple( lineTokens[2] ) ;
                if( operand2Tuple.size() == 2 ) {
                    if( operand2Tuple[0] == "S" ) {
                        int index = std::stoi( operand2Tuple[1] ) ;
                        operand2 = symbolTable.getSymbolAddressFromIndex( index ) ;
                    }
                }
                else {
                    operand2 = std::stoi( operand2Tuple[0] ) ;
                }
                cout << operand1 << " " << operand2 << LBR ; 
                */
                
            }
        }
    }

    vector<string> parseStringTuple( string pair ) {
        pair.erase( pair.begin() , pair.begin() + 1 ) ; 
        pair.erase( pair.end() - 1 , pair.end() ) ; 
        string item = "" ; 
        vector<string> items;
        for( const char& c : pair ) {
            if( c == ',' ) {
                items.push_back( item ) ; 
                item.clear() ; 
            }
            else {
                item += c ; 
            }
        }
        items.push_back( item ) ;
        return items;
    }

    pair<SymbolTable,LiteralTable> loadTables() {
        SymbolTable symbolTable ; 
        LiteralTable literalTable ; 
        fstream inputStream( "symbol_table.dat" , ios::in ) ;
        inputStream.read( (char*) &symbolTable , sizeof( symbolTable ) ) ;
        inputStream.close() ; 
        inputStream.open( "literal_table.dat", ios::in ) ; 
        inputStream.read( (char*) &literalTable , sizeof( literalTable ) ) ;
        inputStream.close() ; 
        return { symbolTable , literalTable }; 
    }

} ;