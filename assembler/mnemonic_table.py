from enum import Enum
from typing import Dict

class MnemonicClass( Enum ):
    IS = 0
    DL = 1
    AD = 2

class Mnemonic:

    def __init__( self , mnemonic_class: MnemonicClass, opcode: int ):
        self.mnemonic_class = mnemonic_class
        self.opcode = opcode

class MnemonicTable:

    mnemonics: Dict[ str , Mnemonic ] = {
         "STOP"     : Mnemonic( MnemonicClass.IS , 0 ) , 
         "ADD"      : Mnemonic( MnemonicClass.IS , 1 ) ,
         "SUBTRACT" : Mnemonic( MnemonicClass.IS , 2 ) ,
         "MULT"     : Mnemonic( MnemonicClass.IS , 3 ) ,
         "MOVER"    : Mnemonic( MnemonicClass.IS , 4 ) ,
         "MOVEM"    : Mnemonic( MnemonicClass.IS , 5 ) ,
         "COMP"     : Mnemonic( MnemonicClass.IS , 6 ) ,
         "BC"       : Mnemonic( MnemonicClass.IS , 7 ) ,
         "DIV"      : Mnemonic( MnemonicClass.IS , 8 ) ,
         "READ"     : Mnemonic( MnemonicClass.IS , 9 ) ,
         "PRINT"    : Mnemonic( MnemonicClass.IS , 10 ) ,
         "START"    : Mnemonic( MnemonicClass.AD , 1 ) ,
         "END"      : Mnemonic( MnemonicClass.AD , 2 ) ,
         "ORIGIN"   : Mnemonic( MnemonicClass.AD , 3 ) ,
         "EQU"      : Mnemonic( MnemonicClass.AD , 4 ) ,
         "LTORG"    : Mnemonic( MnemonicClass.AD , 5 ) ,
         "DC"       : Mnemonic( MnemonicClass.DL , 1 ) ,
         "DS"       : Mnemonic( MnemonicClass.DL , 2 ) ,
    } 

    @staticmethod
    def get_mnemonic( name: str ) -> Mnemonic:
        return MnemonicTable.mnemonics[ name ]
    
    @staticmethod
    def check_if_mnemonic( token: str ) -> bool:
        return token in MnemonicTable.mnemonics
    
