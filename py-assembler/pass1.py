import pickle

condition_codes: dict[ str , int ] = {
    "LT" : 1 , 
    "LE" : 2 , 
    "EQ" : 3 , 
    "GT" : 4 , 
    "GE" : 5 , 
    "ANY" : 6
}

register_codes: dict[ str , int ] = {
    "AREG" : 1 , 
    "BREG" : 2 , 
    "CREG" : 3 , 
    "DREG" : 4
}

mnemonics: dict[ str , tuple[ str , int ] ] = {
    "STOP"      : ( "IS" , 1 ) , 
    "ADD"       : ( "IS" , 2) ,
    "SUB"       : ( "IS" , 3) ,
    "MULT"      : ( "IS" , 4) ,
    "MOVER"     : ( "IS" , 5) ,
    "MOVEM"     : ( "IS" , 6) ,
    "COMP"      : ( "IS" , 7) ,
    "BC"        : ( "IS" , 8) ,
    "DIV"       : ( "IS" , 9) , 
    "READ"      : ( "IS" , 10) , 
    "PRINT"     : ( "IS" , 11) ,

    "START"     : ( "AD" , 1 ) ,
    "END"       : ( "AD" , 2 ) , 
    "ORIGIN"    : ( "AD" , 3 ) ,
    "EQU"       : ( "AD" , 4 ) , 
    "LTORG"     : ( "AD" , 5 ) ,

    "DC"        : ( "DL" , 1 ) ,  
    "DS"        : ( "DL" , 2 )   
} 


symbol_table: list[ tuple[ str , int ] ] = []
def find_symbol( symbol_name: str ) -> tuple[int,int]:
    for i , ( s , addr ) in enumerate(symbol_table):
        if s == symbol_name: return i+1 , addr
    return -1 , -1

def update_symbol( symbol_name: str , addr: int ) -> int:
    for i , ( s , _ ) in enumerate( symbol_table ):
        if s == symbol_name:
            if addr != -1:
                symbol_table[ i ] = ( s , addr )
            return i
    symbol_table.append( ( symbol_name , addr ) )
    return len( symbol_table )



literal_table: list[ tuple[ str , int ]  ] = []
pool_table: list[int] = []
pooltab_ptr: int = 0
def update_literal( literal_name: str , addr: int ) -> int:
    for i , ( l , _ ) in enumerate( literal_table[ pooltab_ptr: ] ):
        if l == literal_name:
            literal_table[ i ] = ( l , addr )
            return i
    literal_table.append( ( literal_name , addr ) )
    return len( literal_table )

def init_literals( lc: int ):
    global pooltab_ptr
    for i , ( l , _ ) in enumerate( literal_table[ pooltab_ptr: ] ):
        literal_table[ i ] = ( l , lc )
        lc += 1
    pooltab_ptr = len( literal_table )


source_file_path: str = input( "Enter source code file path: " ) 
with open( source_file_path , "r" ) as file:
    source_contents: str = file.read()

source_lines: list[str] = source_contents.split( "\n" ) 
source_line_tokens: list[list[str]] = [ line.split() for line in source_lines ]

location_cntr: int = 1

ic_lines: list[str] = []
for line_tokens in source_line_tokens:
    label: str = ""
    mnemonic_str: str = ""
    operand1: str = ""
    operand2: str = ""
    if line_tokens[0] in mnemonics:
        mnemonic_str: str = line_tokens[0]
        if len( line_tokens ) == 2:
            operand1 = line_tokens[1] 
        if len( line_tokens ) == 3:
            operand1 = line_tokens[1]
            operand2 = line_tokens[2]
    else:
        label: str = line_tokens[0]
        mnemonic_str: str = line_tokens[1]
        if len( line_tokens ) == 3:
            operand1 = line_tokens[2]
        if len( line_tokens ) == 4:
            operand1 = line_tokens[2]
            operand2 = line_tokens[3]
    mnemonic_class: str = mnemonics[ mnemonic_str ][0]
    mnemonic_opcode: int = mnemonics[ mnemonic_str ][1]
    ic_line: str = "({},{}) ".format( mnemonic_class , mnemonic_opcode )
    ic_line = "{} ".format( location_cntr if mnemonic_class != "AD" else "   " ) + ic_line

    if mnemonic_class != "DL" and label != "":
        print( label , location_cntr )
        update_symbol( label , location_cntr )
    
    if mnemonic_str == "START":
        location_cntr = int( operand1 )
        ic_line += "(C,{})".format( location_cntr )
    
    if mnemonic_str == "ORIGIN":
        if "+" in operand1 or "-" in operand1:
            symbol_name , constant = operand1.replace( "+" , " " ).replace( "-" , " " ).split()
            _ , symbol_addr = find_symbol(symbol_name) 
            location_cntr = int( eval( operand1.replace( symbol_name , str(symbol_addr ) ) )  )
            ic_line += "(C,{})".format( location_cntr )
        else:
            symbol_index , symbol_addr = find_symbol(symbol_name)
            if symbol_index == -1:
                location_cntr = int( operand1 )
                ic_line += "(C,{})".format( location_cntr )
            else:
                location_cntr = symbol_addr
                ic_line += "(S,{})".format( symbol_index )

    if mnemonic_str == "LTORG":
        init_literals( location_cntr )
            
    if mnemonic_str == "EQU":
        if "+" in operand1 or "-" in operand1:
            symbol_name , constant = operand1.replace( "+" , " " ).replace( "-" , " " ).split()
            symbol_index , symbol_addr = find_symbol(symbol_name) 
            updated_val = int( eval( operand1.replace( symbol_name , str(symbol_addr ) ) )  )
            ic_line += "(S,{}) ".format( symbol_index )
            ic_line += "(C,{})".format( updated_val )
            update_symbol( label , updated_val )
        else:
            symbol_index , symbol_addr = find_symbol(operand1)
            updated_val: int = 0
            if symbol_index == -1:
                updated_val = int( operand1 )
            else:
                updated_val = symbol_addr
            update_symbol( label , updated_val )
            

    if mnemonics[ mnemonic_str ][0] == "IS":
        if mnemonic_str == "READ" or mnemonic_str == "PRINT":
            symbol_index = update_symbol( operand1 , -1 )
            ic_line += "(S,{})".format( symbol_index )
        elif mnemonic_str == "BC":
            symbol_index = update_symbol( operand2 , -1 )
            ic_line += "({}) ".format( condition_codes[operand1] )
            ic_line += "(S,{})".format( symbol_index )
        elif mnemonic_str == "STOP":
            pass
        else:
            if "=" in operand2:
                literval_val = operand2.split( "=" )[1]
                literal_index = update_literal( literval_val , -1 )
                ic_line += "({}) (L,{})".format( register_codes[operand1] , literal_index )
            else:
                symbol_index = update_symbol( operand2 , -1 )
                ic_line += "({}) (S,{})".format( register_codes[operand1] , symbol_index )
        location_cntr += 1

    if mnemonics[ mnemonic_str ][0] == "DL":
        symbol_index = update_symbol( label , location_cntr )
        if mnemonic_str == "DC":
            location_cntr += 1
        elif mnemonic_str == "DS":
            location_cntr += int( operand1 )   
        ic_line += "(S,{}) (C,{})".format( symbol_index , operand1 )

    ic_lines.append( ic_line )


init_literals( location_cntr )
    

print( "-------------- INTERMEDIATE CODE----------------" )
for line in ic_lines:
    print( line )

print( "--------- SYMBOL TABLE -------------" )
for ( s , addr ) in symbol_table:
    print( s , addr )

print( "--------- LITERAL TABLE -------------" )
for ( l , addr ) in literal_table:
    print( l , addr )


with open( "symtab.pkl" , "wb" ) as file:
    pickle.dump( symbol_table , file )
with open( "littab.pkl" , "wb" ) as file:
    pickle.dump( literal_table , file )
with open( "ic.txt" , "w" ) as file:
    for ic_line in ic_lines:
        file.write( ic_line + "\n" )
