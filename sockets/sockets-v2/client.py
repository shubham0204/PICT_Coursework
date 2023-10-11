import socket

HOST = "127.0.0.1"
PORT = 8080

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:
    s.connect( ( HOST , PORT ) )
    for _ in range(50):
        s.send( b"Hello" )
    while True:
        data = s.recv( 1024 )
        if not data:
            break
        print( data )