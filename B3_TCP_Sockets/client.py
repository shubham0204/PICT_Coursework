import socket

#HOST = input( "Enter host address: " )
#PORT = int( input( "Enter port address: " ) )

HOST = "127.0.0.1"
PORT = 8080
BUFFER = 4096

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:

    s.connect( ( HOST , PORT ) )

    while True:
        print( 
        """
        1. Say Hello
        2. Transfer File
        3. Solve arithmetic expression
        """)
        option = int( input( "Enter option: " ) )

        if option == 1:
            message= "[MESSAGE]{}Hello".format( chr( 5 ) )
            s.send( message.encode() )
            response = s.recv( BUFFER ).decode( "ascii" )
            print( "Response from server => " , response )

        elif option == 2:
            file_path = input( "Enter file path: " )
            with open( file_path , "rb" ) as file:
                file_bytes = file.read()
            message = "[FILE]{}{}".format( chr( len( file_bytes ) ) , file_bytes.decode( "ascii" ) )
            s.send( message.encode() )

        elif option == 3:
            expr = input( "Enter expression: " )
            message= "[EXPR]{}{}".format( chr( len( expr ) ) , expr )
            s.send( message.encode() )
            response = s.recv( BUFFER ).decode( "ascii" )
            print( "Response from server => " , response )
