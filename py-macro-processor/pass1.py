class MNTEntry:

    def __init__( self ):
        self.macro_name: str = ""
        self.num_kpd: int = 0
        self.num_pp: int = 0
        self.mdtab_ptr: int = 0 
        self.kpdtab_ptr: int = 0 

class MDTEntry:

    def __init__( self ):
        self.mnemonic: str = ""
        self.operand1: str = ""
        self.operand2: str = ""
        self.operand1_index: int = -1
        self.operand2_index: int = -1

mntab: list[MNTEntry] = []
mdtab: list[MDTEntry] = []
kpdtab: list[tuple[str,str]] = []
pntab_map: dict[ str , list[str] ] = {}

source_path = input( "Enter source path: " )
with open( source_path , "r" ) as file:
    source_contents: str = file.read()
    source_lines: list[str] = source_contents.split( "\n" )
    source_tokens: list[list[str]] = [ line.split() for line in source_lines ]

mdtab_ptr: int = 0
kpdtab_ptr: int = 0
curr_macro_name: str = ""

for i in range( 1 , len( source_tokens ) ):
    line_tokens = source_tokens[i]

    if source_tokens[i-1][0] == "MACRO":
        macro_name: str = line_tokens[0]
        parameters: str = line_tokens[1:]
        pntab: list[str] = []
        num_kpd: int = 0 
        num_pp: int = 0
        for parameter in parameters:
            if "=" in parameter:
                parameter_name , def_val = parameter.split( "=" )
                kpdtab.append( ( parameter_name , def_val ) )
                num_kpd += 1
            else:
                parameter_name = parameter
                num_pp += 1
            pntab.append( parameter_name )
   
        mntab_entry = MNTEntry()
        mntab_entry.macro_name = macro_name
        mntab_entry.num_kpd = num_kpd
        mntab_entry.num_pp = num_pp
        mntab_entry.kpdtab_ptr = kpdtab_ptr
        mntab_entry.mdtab_ptr = mdtab_ptr

        pntab_map[ macro_name ] = pntab
        kpdtab_ptr += num_kpd
        curr_macro_name = macro_name

        mntab.append( mntab_entry )
        
    elif line_tokens[0] != "MEND" and line_tokens[0] != "MACRO":

        mdtab_entry = MDTEntry()
        mnemonic = line_tokens[0]
        mdtab_entry.mnemonic = mnemonic
        pntab: list[str] = pntab_map[ curr_macro_name ]

        param = line_tokens[1]
        if param in pntab:
            mdtab_entry.operand1_index = pntab.index( param )
        mdtab_entry.operand1 = param

        param = line_tokens[2]
        if param in pntab:
            mdtab_entry.operand2_index = pntab.index( param )
        mdtab_entry.operand2 = param

        mdtab.append( mdtab_entry )
        mdtab_ptr += 1

    elif line_tokens[0] == "MEND":
        mdtab_entry = MDTEntry()
        mdtab_entry.mnemonic = "MEND"
        mdtab.append( mdtab_entry )

print( "------------ MNTAB ----------------")   
print( "Name".ljust( 10 ) , "#PP".ljust( 5 ) , "#KP".ljust( 5 ) , "KPDTAB_PTR".ljust( 10 ) , "MDTAB_PTR".ljust( 10 ) )  
for entry in mntab:
    print( 
        entry.macro_name.ljust( 10 ) , 
        str(entry.num_pp).ljust( 5 ) , 
        str(entry.num_kpd).ljust( 5 ) , 
        str(entry.kpdtab_ptr).ljust( 10 ) , 
        str(entry.mdtab_ptr).ljust( 10 )
    )

print( "------------ MDTAB ----------------")   
for entry in mdtab:
    print( 
        entry.mnemonic.ljust( 10 ) , 
        (entry.operand1 if entry.operand1_index == -1 else f"(P,{entry.operand1_index})").ljust(10) , 
        (entry.operand2 if entry.operand2_index == -1 else f"(P,{entry.operand2_index})").ljust(10) ,  
    )
    
print( "------------ KPDTAB ----------------")   
print( "Name".ljust( 10 ) , "Default Value".ljust( 15 ) )
for param in kpdtab:
    print( param[0].ljust( 10 ) , param[1].ljust( 15 ) )

print( "------------- PNTAB -----------------")
for ( macro_name , pntab ) in pntab_map.items():
    print( "PNTAB for macro" , macro_name ) 
    for param in pntab:
        print( param )