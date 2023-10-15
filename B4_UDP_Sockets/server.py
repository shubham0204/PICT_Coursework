import socket

HOST = "127.0.0.1"
PORT = 8080
BUFFER_SIZE = 4096 * 1024 * 1024

with socket.socket( socket.AF_INET , socket.SOCK_DGRAM ) as server_socket:
    server_socket.bind( ( HOST , PORT ) )

    while True:

        file_bytes , address = server_socket.recvfrom( BUFFER_SIZE )

        message = file_bytes.decode()
        file_name_len = ord( message[0] )
        file_name = message[ 1 : file_name_len + 1 ]
        print( file_name )
        file_len = ord( message[ 1 + file_name_len ] )
        file_bytes = message[ file_name_len + 2 : file_name_len + 2 + file_len ].encode()

        with open( file_name , "wb" ) as file:
            file.write( file_bytes )
