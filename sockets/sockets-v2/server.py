import socket

HOST = "127.0.0.1"
PORT = 8080

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:
    s.bind( ( HOST , PORT ) )
    s.listen()
    conn , addr = s.accept()
    with conn:
        next_seq_num = 0
        while True:
            data = conn.recv( 1024 )
            if data != "":
                data = str( data )[2:]
                data = data[:-1]
                packet_num = int( data.split( ":" )[1] )
                print( "Packet:{} received".format( packet_num ) )
                if packet_num == next_seq_num:
                    conn.send( bytes( "ACK:{}".format( next_seq_num ) , 'ascii' ) )
                    print( "ACK:{} sent".format( next_seq_num ) )
                else:
                    conn.send( bytes( "ACK:{}".format( next_seq_num - 1 ) , 'ascii' ) )
                    print( "ACK:{} sent".format( next_seq_num - 1 ) )