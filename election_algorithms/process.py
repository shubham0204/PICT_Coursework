import random

class Process:

    MESSAGE_ELECTION = "ELECTION"
    MESSAGE_OK = "OK"

    def __init__( self , identifier: int , coordinate: bool = False ):
        self.identifier = identifier
        self.coordinate = coordinate

    def process_message( self , sender_identifier: str , incoming_message: str ) -> str:
        if incoming_message == Process.MESSAGE_ELECTION:
            pass
        elif incoming_message == Process.MESSAGE_OK:
            pass

    def __str__( self ) -> str:
        return "process:" + self.identifier