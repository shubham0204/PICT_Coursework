from enum import Enum
from typing import Dict

class MnemonicClass( Enum ):
    IS = 0
    DL = 1
    AD = 2

class Mnemonic:

    def __init__( self , name: str, mnemonic_class: MnemonicClass, opcode: int ):
        self.name = name
        self.mnemonic_class = mnemonic_class
        self.opcode = opcode

    def __str__(self) -> str:
        return self.name

class MnemonicTable:

    mnemonics: Dict[ str , Mnemonic ] = {
         "STOP"     : Mnemonic( "STOP"     , MnemonicClass.IS , 0 ) , 
         "ADD"      : Mnemonic( "ADD"      , MnemonicClass.IS , 1 ) ,
         "SUBTRACT" : Mnemonic( "SUBTRACT" , MnemonicClass.IS , 2 ) ,
         "MULT"     : Mnemonic( "MULT"     , MnemonicClass.IS , 3 ) ,
         "MOVER"    : Mnemonic( "MOVER"    , MnemonicClass.IS , 4 ) ,
         "MOVEM"    : Mnemonic( "MOVEM"    , MnemonicClass.IS , 5 ) ,
         "COMP"     : Mnemonic( "COMP"     , MnemonicClass.IS , 6 ) ,
         "BC"       : Mnemonic( "BC"       , MnemonicClass.IS , 7 ) ,
         "DIV"      : Mnemonic( "DIV"      , MnemonicClass.IS , 8 ) ,
         "READ"     : Mnemonic( "READ"     , MnemonicClass.IS , 9 ) ,
         "PRINT"    : Mnemonic( "PRINT"    , MnemonicClass.IS , 10 ) ,
         "START"    : Mnemonic( "START"    , MnemonicClass.AD , 1 ) ,
         "END"      : Mnemonic( "END"      , MnemonicClass.AD , 2 ) ,
         "ORIGIN"   : Mnemonic( "ORIGIN"   , MnemonicClass.AD , 3 ) ,
         "EQU"      : Mnemonic( "EQU"      , MnemonicClass.AD , 4 ) ,
         "LTORG"    : Mnemonic( "LTORG"    , MnemonicClass.AD , 5 ) ,
         "DC"       : Mnemonic( "DC"       , MnemonicClass.DL , 1 ) ,
         "DS"       : Mnemonic( "DS"       , MnemonicClass.DL , 2 ) ,
    } 

    @staticmethod
    def get_mnemonic( name: str ) -> Mnemonic:
        return MnemonicTable.mnemonics[ name ]
    
    @staticmethod
    def check_if_mnemonic( token: str ) -> bool:
        return token in MnemonicTable.mnemonics
    
