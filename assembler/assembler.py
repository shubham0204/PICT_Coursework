from mnemonic_table import MnemonicTable
from tokenizer import Tokenizer
from typing import List

class Pass1:

    def __init__( self , source_filepath: str ):
        self.source_lines: List[str]  = []
        with open( source_filepath , "r" ) as file:
            self.source_lines = file.readlines()

        for line in self.source_lines:
            p = Tokenizer.get_tokens( line )

Pass1( "sample.txt" )  