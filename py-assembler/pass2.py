ic_file_path: str = input( "Enter IC file path: " )
with open( ic_file_path , "r" ) as file:
    ic_contents: str = file.read()
    ic_lines: list[str] = ic_contents.split( "\n" ) 
    ic_line_tokens: list[list[str]] = [ line.split() for line in ic_lines ]

symtab: list[tuple[str,int]] = []
symtab_filepath: str = input( "Enter symbol table filepath: " )
with open( symtab_filepath , "r" ) as file:
    symtab_contents: str = file.read()
    symtab_lines: list[str] = symtab_contents.split("\n")
    for line in symtab_lines:
        name , addr = line.split()
        symtab.append( ( name , int(addr) ) )

littab: list[tuple[str,int]] = []
littab_filepath: str = input( "Enter literal table filepath: " )
if littab_filepath != "":
    with open( littab_filepath , "r" ) as file:
        littab_contents: str = file.read()
        littab_lines: list[str] = littab_contents.split("\n")
        for line in littab_lines:
            name , addr = line.split()
            littab.append( ( name , int(addr) ) )

for line_tokens in ic_line_tokens:

    if len( line_tokens ) == 4:
        lc: str = line_tokens[0]
        mnemonic_opcode: str = line_tokens[1].strip( "(" ).strip( ")" ).split( "," )[1]
        
        operand1_tokens = line_tokens[2].strip( "(" ).strip( ")" ).split( "," )
        operand1: str = ""
        if len( operand1_tokens ) == 2:
            if operand1_tokens[0] == "S":
                symtab_index = int( operand1_tokens[1] )
                _ , sym_addr = symtab[ symtab_index ]
                operand1 = str(sym_addr)
        else:
            operand1 = operand1_tokens[0]

        operand2_tokens = line_tokens[3].strip( "(" ).strip( ")" ).split( "," )
        operand2: str = ""
        if operand2_tokens[0] == "S":
            symtab_index = int( operand2_tokens[1] )
            _ , sym_addr = symtab[ symtab_index ]
            operand2 = str(sym_addr)
        elif operand2_tokens[0] == "L":
            littab_index = int( operand2_tokens[1] )
            _ , lit_addr = littab[ littab_index ]
            operand2 = str(lit_addr)
        elif operand2_tokens[0] == "C":
            value = operand2_tokens[1]
            if "'" in value:
                value = value.strip( "'" )
            operand2 = value
        
        print( lc , mnemonic_opcode , operand1 , operand2 )

    elif len( line_tokens ) == 2:

        if line_tokens[0].isdigit():
            lc: str = line_tokens[0]
            mnemonic_opcode: str = line_tokens[1].strip( "(" ).strip( ")" ).split( "," )[1]
            print( lc , mnemonic_opcode )
        else:
            mnemonic_opcode: str = line_tokens[0].strip( "(" ).strip( ")" ).split( "," )[1]
            operand1_tokens = line_tokens[1].strip( "(" ).strip( ")" ).split( "," )
            operand1: str = ""
            if len( operand1_tokens ) == 2:
                if operand1_tokens[0] == "S":
                    symtab_index = int( operand1_tokens[1] )
                    _ , sym_addr = symtab[ symtab_index ]
                    operand1 = str(sym_addr)
            else:
                operand1 = operand1_tokens[0]
            print( mnemonic_opcode , operand1 )

