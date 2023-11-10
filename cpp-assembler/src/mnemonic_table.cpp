#include <string>
#include <unordered_map>
using std::string, std::unordered_map;

enum MnemonicClass {
    IS,
    DL,
    AD
} ; 

class Mnemonic {

    public:

    MnemonicClass mclass;
    int opCode;

    Mnemonic(){
    }

    Mnemonic( MnemonicClass mclass , int opCode ) {
        this -> mclass = mclass;
        this -> opCode = opCode;
    }

    string getClass() {
        if( mclass == MnemonicClass::IS ) {
            return "IS" ; 
        }
        else if ( mclass == MnemonicClass::AD ) {
            return "AD" ; 
        }
        else if ( mclass == MnemonicClass::DL ) {
            return "DL" ; 
        }
        else {
            return "" ;
        }
    }

} ; 

class MnemonicTable {

    unordered_map<string,Mnemonic> mnemonics = {
         { "STOP" , Mnemonic( MnemonicClass::IS , 0 ) } , 
         { "ADD" , Mnemonic( MnemonicClass::IS , 1 ) } ,
         { "SUB" , Mnemonic( MnemonicClass::IS , 2 ) } ,
         { "MULT" , Mnemonic( MnemonicClass::IS , 3 ) } ,
         { "MOVER" , Mnemonic( MnemonicClass::IS , 4 ) } ,
         { "MOVEM" , Mnemonic( MnemonicClass::IS , 5 ) } ,
         { "COMP" , Mnemonic( MnemonicClass::IS , 6 ) } ,
         { "BC" , Mnemonic( MnemonicClass::IS , 7 ) } ,
         { "DIV" , Mnemonic( MnemonicClass::IS , 8 ) } ,
         { "READ" , Mnemonic( MnemonicClass::IS , 9 ) } ,
         { "PRINT" , Mnemonic( MnemonicClass::IS , 10 ) } ,

         { "START" , Mnemonic( MnemonicClass::AD , 1 ) } ,
         { "END" , Mnemonic( MnemonicClass::AD , 2 ) } ,
         { "ORIGIN" , Mnemonic( MnemonicClass::AD , 3 ) } ,
         { "EQU" , Mnemonic( MnemonicClass::AD , 4 ) } ,
         { "LTORG" , Mnemonic( MnemonicClass::AD , 5 ) } ,

         { "DC" , Mnemonic( MnemonicClass::DL , 1 ) } ,
         { "DS" , Mnemonic( MnemonicClass::DL , 2 ) } ,
    } ; 

    public:

    Mnemonic getMnemonic( string name ) {
        return mnemonics[ name ] ; 
    }

    bool isMnemonic( string token ) {
        return mnemonics.find( token ) != mnemonics.end() ; 
    }

} ; 


