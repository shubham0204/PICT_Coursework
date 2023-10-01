import random

class Process:

    MESSAGE_ELECTION = "ELECTION"
    MESSAGE_OK = "OK"
    MESSAGE_NOT_OK = "NOT_OK"
    ACTIVE_PROB = 0.9

    def __init__( self , identifier: int , coordinate: bool = False ):
        self.identifier = identifier
        self.coordinate = coordinate

    def process_message( self , sender_identifier: str , incoming_message: str ) -> str:
        if Process.__is_active():
            return Process.MESSAGE_OK
        else:
            return Process.MESSAGE_NOT_OK

    @classmethod
    def __is_active( cls ) -> bool:
        return random.uniform( 0 , 1 ) <= Process.ACTIVE_PROB

    def __str__( self ) -> str:
        return "process:" + str(self.identifier)