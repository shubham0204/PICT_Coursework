import socket
import os

HOST = "127.0.0.1"
PORT = 8080

with socket.socket( socket.AF_INET , socket.SOCK_DGRAM ) as client_socket:

    while True:
        file_path = input( "Enter file path: " )
        with open( file_path , "rb" ) as file:
            file_bytes = file.read()
        file_name = os.path.basename( file_path )
        message = "{}{}".format( chr( len( file_name ) ) , file_name )
        message += "{}{}".format( chr( len( file_bytes ) ) , file_bytes )
        client_socket.sendto( message.encode() , ( HOST , PORT ) )