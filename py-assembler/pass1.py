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


symtab: list[ tuple[ str , int ] ] = []
def find_symbol( symbol_name: str ) -> tuple[int,int]:
    # Find symbol with name `symbol_name` and
    # return its index and address if found
    # else -1 for both
    for i , ( s , addr ) in enumerate(symtab):
        if s == symbol_name: return i+1 , addr
    return -1 , -1

def update_symbol( symbol_name: str , addr: int ) -> int:
    # Add symbol with name `symbol_name` and address `addr`
    # if addr == -1, add a new symbol
    # else, update the address of the symbol
    # and return the index of the symbol from the table
    for i , ( s , _ ) in enumerate( symtab ):
        if s == symbol_name:
            if addr != -1:
                symtab[ i ] = ( s , addr )
            return i
    symtab.append( ( symbol_name , addr ) )
    return len( symtab )

# Allocate littab and pooltab with 10 empty entries
littab: list[ tuple[ str , int ]  ] = [ ( '' , -1 ) for _ in range(10) ]
pooltab: list[int] = [ -1 for _ in range(10) ]
littab_ptr: int = 0
pooltab_ptr: int = 0
pooltab[pooltab_ptr] = 0

def init_literals():
    global pooltab_ptr , location_cntr
    for i in range( pooltab[pooltab_ptr] , littab_ptr ):
        littab[i] = ( littab[i][0] , location_cntr )
        location_cntr += 1
    pooltab_ptr += 1
    pooltab[ pooltab_ptr ] = littab_ptr

source_file_path: str = input( "Enter source code file path: " ) 
with open( source_file_path , "r" ) as file:
    source_contents: str = file.read()
source_lines: list[str] = source_contents.split( "\n" ) 
source_line_tokens: list[list[str]] = [ line.split() for line in source_lines ]

location_cntr: int = 1
ic_lines: list[str] = []

for line_tokens in source_line_tokens:

    # Each line in the source will be parsed in the following format,
    # <label> <mnemonic> <operand1> <operand2>
    label: str = ""
    mnemonic_str: str = ""
    operand1: str = ""
    operand2: str = ""
    if line_tokens[0] in mnemonics:
        # Assuming format is,
        # <mnemonic> <operand1> OR
        # <mnemonic> <operand1> <operand2>
        mnemonic_str: str = line_tokens[0]
        if len( line_tokens ) == 2:
            operand1 = line_tokens[1] 
        if len( line_tokens ) == 3:
            operand1 = line_tokens[1]
            operand2 = line_tokens[2]
    else:
        # Assuming format is,
        # <label> <mnemonic> <operand1> OR
        # <label> <mnemonic> <operand1> <operand2>
        label: str = line_tokens[0]
        mnemonic_str: str = line_tokens[1]
        if len( line_tokens ) == 3:
            operand1 = line_tokens[2]
        if len( line_tokens ) == 4:
            operand1 = line_tokens[2]
            operand2 = line_tokens[3]

    mnemonic_class: str = mnemonics[ mnemonic_str ][0]
    mnemonic_opcode: int = mnemonics[ mnemonic_str ][1]
    # Append ( <class> , <opcode> ) to IC output line
    # Append loc_cntr is mnemonic class is not AD
    ic_line: str = "({},{}) ".format( mnemonic_class , mnemonic_opcode )
    ic_line = "{} ".format( location_cntr if mnemonic_class != "AD" else "   " ) + ic_line

    # Case 1: Label present
    if mnemonic_class != "DL" and label != "":
        update_symbol( label , location_cntr )


    # Case 2: LTORG present
    if mnemonic_str == "LTORG":
        init_literals()


    # Case 3: START or ORIGIN
    if mnemonic_str == "START":
        location_cntr = int( operand1 )
        ic_line += "(C,{})".format( location_cntr )
    
    if mnemonic_str == "ORIGIN":
        if "+" in operand1 or "-" in operand1:
            # Assuming format is,
            # ORIGIN A+3 OR
            # ORIGIN B-4 where A and B are symbols
            symbol_name , constant = operand1.replace( "+" , " " ).replace( "-" , " " ).split()
            _ , symbol_addr = find_symbol(symbol_name) 
            location_cntr = int( eval( operand1.replace( symbol_name , str(symbol_addr ) ) )  )
            ic_line += "(C,{})".format( location_cntr )
        else:
            # Assuming format is,
            # ORIGIN B where B is a symbol
            symbol_index , symbol_addr = find_symbol(symbol_name)
            if symbol_index == -1:
                location_cntr = int( operand1 )
                ic_line += "(C,{})".format( location_cntr )
            else:
                location_cntr = symbol_addr
                ic_line += "(S,{})".format( symbol_index )


    # Case 4: EQU present            
    if mnemonic_str == "EQU":
        if "+" in operand1 or "-" in operand1:
            # Assuming format is,
            # B EQU A+3 OR
            # C EQU B-4 where A, B and C are symbols
            symbol_name , constant = operand1.replace( "+" , " " ).replace( "-" , " " ).split()
            symbol_index , symbol_addr = find_symbol(symbol_name) 
            updated_val = int( eval( operand1.replace( symbol_name , str(symbol_addr ) ) )  )
            ic_line += "(S,{}) ".format( symbol_index )
            ic_line += "(C,{})".format( updated_val )
            update_symbol( label , updated_val )
        else:
            # Assuming format is,
            # B EQU A OR
            # C EQU B where A, B and C are symbols
            symbol_index , symbol_addr = find_symbol(operand1)
            updated_val: int = 0
            if symbol_index == -1:
                updated_val = int( operand1 )
            else:
                updated_val = symbol_addr
            update_symbol( label , updated_val )


    # Case 5: Data declaration statements (DC/DS statements)
    if mnemonics[ mnemonic_str ][0] == "DL":
        symbol_index = update_symbol( label , location_cntr )
        if mnemonic_str == "DC":
            location_cntr += 1
        elif mnemonic_str == "DS":
            location_cntr += int( operand1 )   
        ic_line += "(S,{}) (C,{})".format( symbol_index , operand1 )


    # Case 6: Imperative statements
    if mnemonics[ mnemonic_str ][0] == "IS":

        if mnemonic_str == "READ" or mnemonic_str == "PRINT":
            # READ and PRINT have a single operand
            symbol_index = update_symbol( operand1 , -1 )
            ic_line += "(S,{})".format( symbol_index )

        elif mnemonic_str == "BC":
            # BC has 
            # operand1 -> conditional_code
            # operand2 -> symbol
            symbol_index = update_symbol( operand2 , -1 )
            ic_line += "({}) ".format( condition_codes[operand1] )
            ic_line += "(S,{})".format( symbol_index )

        elif mnemonic_str == "STOP":
            pass
        else:
            # All other imperative mnemonics having two operands where,
            # operand1 -> register
            # operand2 -> literal OR symbol
            if "=" in operand2:
                # operand2 is a literal (contains '=')
                literval_val = operand2.split( "=" )[1]
                ic_line += "({}) (L,{})".format( register_codes[operand1] , littab_ptr )
                littab[littab_ptr] = ( literval_val , -1 )
                littab_ptr += 1
            else:
                # operand2 is a symbol
                symbol_index = update_symbol( operand2 , -1 )
                ic_line += "({}) (S,{})".format( register_codes[operand1] , symbol_index )
        location_cntr += 1

    ic_lines.append( ic_line )


# Perform case 2 (LTORG)
init_literals()
    
print( "-------------- INTERMEDIATE CODE----------------" )
for line in ic_lines:
    print( line )

print( "--------- SYMBOL TABLE -------------" )
for ( s , addr ) in symtab:
    print( s , addr )

print( "--------- LITERAL TABLE -------------" )
for ( l , addr ) in littab[ : littab_ptr ]:
    print( l , addr )

print( "---------- POOL TABLE --------------- " )
for i in pooltab[ : pooltab_ptr ]:
    print( i )