import socket
import sys

print( 
    """
    Choose option:
    1. Get IP from Name
    2. Get Name from IP
    """
)
option = int( input( "Enter option: " ) )
if option == 1:
    name = input( "Enter name: " ) 
    print( socket.gethostbyname( name ) ) 
elif option == 2:
    addr = input( "Enter IP: " )
    print( socket.gethostbyaddr( addr )[0] )