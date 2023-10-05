import socket
import random

HOST = "127.0.0.1"
PORT = 8080
NO_ACK_PROB = 0.3

def send_ack() -> bool:
    return random.uniform( 0 , 1 ) >= NO_ACK_PROB

def int_to_bytes( x: int ) -> bytes:
    return x.to_bytes( 24 , "little" )

def bytes_to_int( x: bytes ) -> int:
    return int.from_bytes( x , "little" , signed=False )

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:
    s.bind( ( HOST , PORT ) )
    s.listen()
    conn , addr = s.accept()
    with conn:
        Rn = 0
        while True:
            data = bytes_to_int( conn.recv( 24 ) )
            packet_num = data
            print( "Packet:{} received".format( packet_num ) )
            if packet_num == Rn:
                Rn += 1
            if send_ack():
                conn.send( int_to_bytes( Rn ) )
                print( "ACK:{} sent".format( Rn ) )
            else:
                print( "ACK for {} not sent".format( Rn ) )