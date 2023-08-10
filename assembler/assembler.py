from mnemonic_table import MnemonicTable
from mnemonic_table import MnemonicClass
from codes import RegisterCodes
from codes import ConditionCodes
from tokenizer import Tokenizer
from tokenizer import Instruction
from typing import List

class Pass1:

    def __init__( self , source_filepath: str ):
        self.source_lines: List[str]  = []
        self.tokens: List[Instruction] = []
        with open( source_filepath , "r" ) as file:
            self.source_lines = file.readlines()
        for line in self.source_lines:
            self.tokens.append( Tokenizer.get_tokens( line ) )
            print( Tokenizer.get_tokens( line ).mnemonic.name ) 

    def analyze( self ):
        location_counter = 0

        for line in self.tokens:
            if line.mnemonic.name == "START" or line.mnemonic.name == "ORIGIN":
                location_counter = int(line.operand1)
            if line.mnemonic.name == "EQU":
                pass
            if line.mnemonic.mnemonic_class == MnemonicClass.IS:
                if line.mnemonic.name == "BC":
                    pass
                elif line.mnemonic.name == "STOP":
                    pass 
                elif line.mnemonic.name == "PRINT":
                    pass
                elif line.mnemonic.name == "READ":
                    
            if line.mnemonic.name == "END":
                break

Pass1( "sample.txt" )  