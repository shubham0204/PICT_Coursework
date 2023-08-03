from mnemonic_table import MnemonicTable

class Instruction:

    def __init__( self ):
        self.label: str = ""
        self.mnemonic_name: str = ""
        self.operand1: str = ""
        self.operand2: str = ""

    def __str__( self ) -> str:
        return "{} {} {} {}".format( self.label , self.mnemonic_name , self.operand1 , self.operand2 )
    

class Tokenizer:

    @staticmethod
    def get_tokens( instruction_str: str ) -> Instruction:
        tokens = instruction_str.split()
        tokens = [ token.upper() for token in tokens ]
        instruction = Instruction()
        if MnemonicTable.check_if_mnemonic( tokens[0] ):
            instruction.mnemonic_name = tokens[0]
            if len( tokens ) == 2:
                instruction.operand1 = tokens[1]
            elif len( tokens ) == 3:
                instruction.operand1 = tokens[1] 
                instruction.operand2 = tokens[2] 
        elif MnemonicTable.check_if_mnemonic( tokens[1] ):
            instruction.label = tokens[0]
            instruction.mnemonic_name = tokens[1]
            if len( tokens ) == 3:
                instruction.operand1 = tokens[2]
            elif len( tokens ) == 4:
                instruction.operand1 = tokens[2] 
                instruction.operand2 = tokens[3]
        return instruction
