import socket

#HOST = input( "Enter host address: " )
#PORT = int( input( "Enter port address: " ) )

HOST = "127.0.0.1"
PORT = 8080

with socket.socket( socket.AF_INET , socket.SOCK_STREAM ) as s:
    s.bind( ( HOST , PORT ) )
    s.listen()
    conn , addr = s.accept()
    with conn:

        while True:
            data = conn.recv( 1024 )
    
            if "[MESSAGE]" in data.decode( "ascii" ):
                expr = data.decode( "ascii" )
                expr_start = expr.find( "[MESSAGE]" )
                expr_len_offset = 9
                expr_len = ord( expr[ expr_len_offset ] )
                expr_text = expr[ expr_len_offset + 1 : expr_len_offset + 1 + expr_len ]
                conn.send( expr_text.encode() )
    
            elif "[FILE]" in data.decode( "ascii" ):
                blob = data.decode( "ascii" )
                blob_start = blob.find( "[FILE]" )
                blob_len_offset = 6
                blob_len = ord( blob[ blob_len_offset ] )
                blob_content = blob[ blob_len_offset + 1 : blob_len_offset + 1 + blob_len ].encode()
                print( blob_len )
                with open( "received_file.txt" , "wb" ) as file:
                    file.write( blob_content )
    
            if "[EXPR]" in data.decode( "ascii" ):
                expr = data.decode( "ascii" )
                expr_start = expr.find( "[EXPR]" )
                expr_len_offset = 6
                expr_len = ord( expr[ expr_len_offset ] )
                expr_text = expr[ expr_len_offset + 1 : expr_len_offset + 1 + expr_len ]
                if "+" in expr_text:
                    op1 , op2 = map( int , expr_text.split( "+" ) )
                    conn.send( str( op1 + op2 ).encode() )
                elif "-" in expr_text:
                    op1 , op2 = map( int , expr_text.split( "-" ) )
                    conn.send( str( op1 - op2 ).encode() )
                elif "*" in expr_text:
                    op1 , op2 = map( int , expr_text.split( "*" ) )
                    conn.send( str( op1 * op2 ).encode() )
                elif "/" in expr_text:
                    op1 , op2 = map( int , expr_text.split( "/" ) )
                    conn.send( str( op1 / op2 ).encode() )
    