
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

def find_symbol( symbol_name: str ) -> int:
    for ( s , addr ) in symbol_table:
        if s == symbol_name: return addr
    return -1

source_file_path: str = input( "Enter source code file path:" ) 
with open( source_file_path , "r" ) as file:
    source_contents: str = file.read()

source_lines: list[str] = source_contents.split( "\n" ) 
source_line_tokens: list[list[str]] = [ line.split() for line in source_lines ]

location_cntr: int = 1
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

    if mnemonics[ mnemonic_str ][0] != "DL" and label != "":
        symbol_table.append( ( label , location_cntr ) )
    
    if mnemonic_str == "START":
        location_cntr = int( operand1 )
    
    if mnemonic_str == "ORIGIN":
        if "+" in operand1:
            # TODO: Compute expression here
            pass
        else:
            find_symbol_result = find_symbol( operand1 )
            if find_symbol_result == -1:
                location_cntr = int( operand1 )
            else:
                location_cntr = find_symbol_result
            
    if mnemonic_str == "EQU":
        if "+" in operand1:
             # TODO: Compute expression here
            pass
        else:
            find_symbol_result = find_symbol( operand1 )
            updated_val: int = 0
            if find_symbol_result == -1:
                updated_val = int( operand1 )
            else:
                updated_val = find_symbol_result
            for i , ( s , addr ) in enumerate( symbol_table ):
                if s == label:
                    symbol_table[ i ] = ( s , updated_val )
                    break

    if mnemonics[ mnemonic_str ][0] == "IS":
        if mnemonic_str == "READ" or mnemonic_str == "PRINT" or mnemonic_str == "BC":
            if find_symbol( operand1 ) == -1:
                symbol_table.append( ( operand1 , -1 ) )
        # TODO: Add STOP here
        else:
            if "=" in operand2:
                # TODO: Add in literal table here
                pass
            else:
                if find_symbol( operand1 ) == -1:
                    symbol_table.append( ( operand1 , -1 ) )
        location_cntr += 1

    if mnemonics[ mnemonic_str ][0] == "DL":
        for i , ( s , addr ) in enumerate( symbol_table ):
            if s == label:
                symbol_table[ i ] = ( s , location_cntr )
                break
        if mnemonic_str == "DC":
            location_cntr += 1
        elif mnemonic_str == "DS":
            location_cntr += int( operand1 )    
