import socket
import time

HOST = "127.0.0.1"
PORT = 8080


def int_to_bytes( x: int ) -> bytes:
    return x.to_bytes( 24 , "little" )

def bytes_to_int( x: bytes ) -> int:
    return int.from_bytes( x , "little" , signed=False )

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:
    s.connect( ( HOST , PORT ) )
    s.settimeout(1)

    Sb = 0
    Rn = 0
    N = 4

    timer_status = False
    timer_start = time.time()
    timer_out_secs = 5
    num_packets = 0

    while num_packets < 50:
        if Rn < Sb + N:
            s.send( int_to_bytes( Rn ) )
            print( "Packet:{} sent".format( Rn ) )
            num_packets += 1
            Rn += 1

        try:
            data = bytes_to_int( s.recv( 24 ) )
            ack_num = data
            print( "ACK:{} received".format( ack_num ) )
            Sb = ack_num + 1
            print( "Window slided" )
            if Sb == Rn:
                timer_status = False
                timer_start = time.time()
            else:
                timer_status = True
                timer_start = time.time()

        except socket.timeout:
            pass

        if timer_status and (time.time() - timer_start) >= timer_out_secs:
            timer_status = True
            timer_start = time.time()
            for i in range( Sb , Rn ):
                s.send( int_to_bytes( i ) )
                print( "Packet:{} sent".format( i ) )
                num_packets += 1
                time.sleep( 1 )