import time
import random

SUCCESS_PROB = 0.7
def gen_random() -> bool:
    return random.uniform( 0.0 , 1.0 ) < SUCCESS_PROB

def go_back_n( num_bits: int , num_frames: int ):
    window_size: int = 2**num_bits - 1
    print( "WINDOW SIZE:" , window_size )
    tr: int = 0
    i: int = 0
    while i < num_frames:

        inc: int = 0

        j: int = i
        while j < i + window_size and j <= num_frames:
            print( "=> SENT FRAME" , j )
            tr += 1
            time.sleep( 1 )
            j += 1

        j = i
        while j < i + window_size and j <= num_frames:
            flag: int = gen_random()
            if flag:
                print( "<= ACK RECEIVED FOR" , j )
                tr += 1
                inc += 1
                time.sleep( 1 )
            else:
                print( "<=x ACK NOT RECEIVED FOR" , j )
                time.sleep( 1 )
                print( "(.) RETRANSMITTING THE CURRENT WINDOW" )
                time.sleep( 1 )
                break
            j += 1

        i += inc
        print( "\n\n WINDOW SLIDED \n\n" )


def selective_repeat( num_bit: int , num_frames: int ):
    window_size: int = 2**( num_bit - 1 )
    print( "WINDOW SIZE:" , window_size )
    dropped_packets: list[int] = [ 0 for _ in range( num_frames + 1 ) ]
    MAX_INPUT = 1000
    ack_rec: int = 0
    last_packet: int = 0
    last_packet_ack: int = last_packet
    insert_here = 1

    for i in range( 0 , num_frames + 1 ):
        dropped_packets[i] = MAX_INPUT

    while ack_rec < num_frames:

        i = 1
        while i <= window_size and ack_rec < num_frames:
            if dropped_packets[i] != MAX_INPUT:
                print( "=> SENT FRAME" , dropped_packets[i] )
                time.sleep( 1 )
            else:
                if last_packet == num_frames:
                    continue
                print( "=> SENT FRAME" , last_packet + 1 )
                last_packet += 1
                insert_here += 1
                time.sleep( 1 )
            i += 1

        i = 1
        while i <= window_size and ack_rec < num_frames:

            flag: bool = gen_random()

            if flag:
                if dropped_packets[ i ] != MAX_INPUT:
                    print( "<= ACK RECEIVED FOR FRAME" , dropped_packets[i] )
                    time.sleep( 1 )
                    dropped_packets[i] = MAX_INPUT
                else:
                    if last_packet_ack == num_frames:
                        continue
                    print( "<= ACK RECEIVED FOR FRAME" , last_packet_ack + 1 )
                    time.sleep( 1 )
                    last_packet_ack += 1
                ack_rec += 1
                print( "Window slided" )
            else:
                if dropped_packets[i] != MAX_INPUT:
                    print( "<=x ACK NOT RECEIVED FOR FRAME" , dropped_packets[i] ) 
                    time.sleep( 1 )
                else:
                    if last_packet_ack == num_frames:
                        continue
                    print( "<=x ACK NOT RECEIVED FOR FRAME" , last_packet_ack + 1 )
                    time.sleep( 1 )
                    dropped_packets[ insert_here ] = last_packet_ack + 1
                    last_packet_ack += 1
                    insert_here += 1
            i += 1


        dropped_packets[ 1 : num_frames + 2 ] = list( sorted( dropped_packets[ 1 : num_frames + 2 ] ) )
        for i in range( 1 , num_frames + 2 ):
            if dropped_packets[i] == MAX_INPUT:
                insert_here = i
                break

num_bits = int( input( "Enter number of bits: " ) )
num_frames = int( input( "Enter number of frames: " ) )

while True:

    print( 
        """
        Choose ARQ Protocol:
        1. Go-Back-N
        2. Selective Repeat
        """
    )
    option = int( input( "Enter option: " ) )
    if option == 1:
        go_back_n( num_bits , num_frames )
    elif option == 2:
        selective_repeat( num_bits , num_frames )
                
                
                    
