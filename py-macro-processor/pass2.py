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

print( "Enter MDTAB entries:" )
num_entries = int( input( "Enter number of entries in MDTAB: " ) )
mdtab = []
for _ in range( num_entries ):
    entry = MDTEntry()
    entry.mnemonic = input( "Enter mnemonic: " )
    entry.operand1 = input( "Enter operand 1: " )
    if entry.operand1.isdigit():
        entry.operand1_index = int( entry.operand1 )
    entry.operand2 = input( "Enter operand 2: " )
    if entry.operand2.isdigit():
        entry.operand2_index = int( entry.operand2 )
    mdtab.append( entry )


print( "Enter KPDTAB entries:" )
num_entries = int( input( "Enter number of entries in KPDTAB: " ) )
kpdtab = []
for _ in range( num_entries ):
    kpdtab.append( ( 
        input( "Enter parameter name: " ) , 
        input( "Enter parameter default value: " )
    ) )

print( "Enter MNTAB entries:" )
num_entries = int( input( "Enter number of entries in MNTAB: " ) )
mntab = []
for _ in range( num_entries ):
    entry = MNTEntry()
    entry.macro_name = input( "Enter macro name: " )
    entry.num_kpd = int( input( "Enter num. of keyword parameters: " ) )
    entry.num_pp = int( input( "Enter num. of positional parameters: " ) )
    entry.mdtab_ptr = int( input( "Enter mdtab ptr: " ) )
    entry.kpdtab_ptr = int( input( "Enter kpdtab ptr: " ) )
    mntab.append( entry )

print( "Enter PNTAB entries:" )
pntab_map = dict()
for macro in mntab:
    print( f"Enter parameters for macro {macro.macro_name}: " )
    pntab = []
    for _ in range( macro.num_kpd + macro.num_pp ):
        pntab.append( input( "Enter parameter name: " ) )
    pntab_map[ macro.macro_name ] = pntab

call_statement = input( "Enter call statement: " )
call_tokens: list[str] = call_statement.split()

macro_name = call_tokens[0]
pntab: list[str] = pntab_map[ macro_name ]
actual_params: list[str] = call_tokens[ 1: ] 

mdtab_ptr = 0
kpdtab_ptr = 0
num_kpd = 0
for entry in mntab:
    if entry.macro_name == macro_name:
        mdtab_ptr = entry.mdtab_ptr
        kpdtab_ptr = entry.kpdtab_ptr
        num_kpd = entry.num_kpd
        break

aptab: dict[ str , str ] = {}
for name , val in kpdtab[ kpdtab_ptr: kpdtab_ptr + num_kpd ]:
    aptab[ name ] = val
for i , param in enumerate(actual_params):
    if "=" in param:
        def_param , val = param.split( "=" )
        aptab[ def_param ] = val
    else:
        aptab[ pntab[i] ] = param

print( "--------------- EXPANDED CODE -------------------" )
curr_entry = mdtab[ mdtab_ptr ]
while curr_entry.mnemonic != "MEND":

    op1: str = ""
    if curr_entry.operand1_index != -1:
        op1 = aptab[ pntab[ curr_entry.operand1_index] ]
    else:
        op1 = curr_entry.operand1
    
    op2: str = ""
    if curr_entry.operand2_index != -1:
        op2 = aptab[ pntab[ curr_entry.operand2_index] ]
    else:
        op2 = curr_entry.operand2

    print( 
        " + " , 
        curr_entry.mnemonic.ljust( 10 ) , 
        op1.ljust(10) , 
        op2.ljust(10) ,  
    )

    mdtab_ptr += 1
    curr_entry = mdtab[ mdtab_ptr ]

print( "---------- APTAB --------------" )
for ( name , val ) in aptab.items():
    print( name , val )