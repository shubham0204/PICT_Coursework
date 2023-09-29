import socket
import time

HOST = "127.0.0.1"
PORT = 8080
WINDOW_SIZE = 4

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:
    s.connect( ( HOST , PORT ) )

    send_base = 0
    next_seq_num = 0

    timer_status = False
    timer_start = time.time()
    timer_out_secs = 10
    num_packets = 0

    while num_packets < 25:
        if next_seq_num < send_base + WINDOW_SIZE:
            s.send( bytes( "Packet:{}".format( next_seq_num ) , 'ascii' ) )
            print( "Packet:{} sent".format( next_seq_num ) )
            num_packets += 1
            next_seq_num += 1
        data = s.recv( 1024 )
        if data != "":
            data = str( data )[2:]
            data = data[:-1]
            ack_num = int( data.split( ":" )[1] )
            print( "ACK:{} received".format( ack_num ) )
            send_base = ack_num + 1
            if send_base == next_seq_num:
                timer_status = False
                timer_start = time.time()
            else:
                timer_status = True
                timer_start = time.time()
        if timer_status and (time.time() - timer_start) >= timer_out_secs:
            timer_status = True
            timer_start = time.time()
            for i in range( send_base , next_seq_num ):
                s.send( b"Packet:{}".format( next_seq_num ) )
                print( "Packet:{} sent".format( next_seq_num ) )
                num_packets += 1