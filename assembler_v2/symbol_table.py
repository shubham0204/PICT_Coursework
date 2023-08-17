from typing import Dict

class Symbol:
    
    def __init__( self , symbol_name: str, address: int ):
        self.symbol_name = symbol_name
        self.address = address

class SymbolTable:

    def __init__( self ):
        self.symbols: Dict[ str , Symbol ] = {}

    def update( self , name, address=None ):
        if address is None:
            self.symbols[ name ] = Symbol( name , 0 )
        else:
            self.symbols[ name ].address = address
