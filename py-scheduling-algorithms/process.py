
class Process:

    def __init__( self ):
        self.id : int = 0
        self.priority : int = 0
        self.at : int = 0
        self.bt : int = 0
        self.ct : int = 0 
        self.tat : int = 0
        self.wt : int = 0 
        self.rt : int = 0

    def calc_params( self ):
        self.tat = self.ct - self.at
        self.wt = self.tat - self.bt

    def __str__( self ) -> str:
        return f"process: {self.id} AT = {self.at} , BT = {self.bt} , CT = {self.ct} , TAT = {self.tat} , WT = {self.wt} , RT = {self.rt} , PRIORITY = {self.priority}"