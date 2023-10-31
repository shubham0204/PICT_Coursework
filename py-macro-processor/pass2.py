import pickle

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

with open( "mdtab.pkl" , "rb" ) as file:
    mdtab: list[MDTEntry] = pickle.load( file )
with open( "kpdtab.pkl" , "rb" ) as file:
    kpdtab: list[tuple[str,str]] = pickle.load( file )
with open( "mntab.pkl" , "rb" ) as file:
    mntab: list[MNTEntry] = pickle.load( file )
with open( "pntab_map.pkl" , "rb" ) as file:
    pntab_map: dict[str,list[str]] = pickle.load( file )

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
        aptab[ pntab[i] ] = val
    else:
        aptab[ pntab[i] ] = param


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

    print( curr_entry.mnemonic , op1 , op2 )

    mdtab_ptr += 1
    curr_entry = mdtab[ mdtab_ptr ]

print( "---------- APTAB --------------" )
for ( name , val ) in aptab.items():
    print( name , val )