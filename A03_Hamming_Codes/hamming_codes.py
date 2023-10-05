import random

def decimal_to_binary( x: int ) -> list[int]:
    p = x
    output: list[int] = []
    while p != 0:
        m = p // 2
        output.append( p % 2 )
        p = m
    return output[::-1]

def binary_to_decimal( num: list[int] ) -> int:
    output = 0
    for i in range( len( num ) - 1 , -1 , -1 ):
        output += 2**( len(num) - 1 - i ) * num[i]
    return output

def list_to_str( l: list[int] ) -> str:
    return "".join( [ str(bit) for bit in l ] )

def get_even_parity( seq: list[int] ) -> int:
    return int( sum(seq) % 2 != 0 )

def get_odd_parity( seq: list[int] ) -> int:
    return int( sum(seq) % 2 == 0 )

def encode( message: list[int] , parity: str ) -> tuple[ list[int] , int ]:
    m = len( message )

    parity_func = get_even_parity if parity == "even" else get_odd_parity

    # Calculate number of redundant bits
    r = 0
    while 2**r < m + r + 1:
        r += 1
    code_word = [ 0 for _ in range( m + r ) ]
    parity_positions = [ 2**i - 1 for i in range(r) ]
    data_positions = [ i for i in range( m + r ) if i not in parity_positions ]
    
    # Fill data bits in code_word
    for i , pos in enumerate( data_positions ):
        code_word[ pos ] = int(message[i])
    
    # Fill parity bits in code_word
    for i , pos in enumerate( parity_positions ):
        parity_seq: list[int] = []
        take = True
        take_count = 2**i
        for j in range( pos , len(code_word) ):
            if take:
                parity_seq.append( code_word[j] )
                take_count -= 1
            else:
                take_count += 1
            if take_count == 0:
                take = False
            elif take_count == 2**i:
                take = True

        code_word[ pos ] = parity_func( parity_seq )

    return code_word , r

def decode( code_word: list[int] , r: int , parity: str ) -> dict[ str , int ]:
    parity_func = get_even_parity if parity == "even" else get_odd_parity

    parity_positions = [ 2**i - 1 for i in range(r) ]
    parity_bits: list[int] = []
    for i , pos in enumerate( parity_positions ):
        parity_seq: list[int] = []
        take = True
        take_count = 2**i
        for j in range( pos , len(code_word) ):
            if take:
                parity_seq.append( code_word[j] )
                take_count -= 1
            else:
                take_count += 1
            if take_count == 0:
                take = False
            elif take_count == 2**i:
                take = True
        parity_bits.append( parity_func( parity_seq ) )

    return parity_bits
    
parity = input( "Which parity do we need? ([even],odd) => " )
parity = "even" if parity == "" else "odd" 

while True:

    print( "---------- Transmitter -----------" )

    input_message_str = input( "Enter message: " )
    input_chars = list( input_message_str )
    input_chars_ascii = [ ord( c ) for c in input_chars ]

    bin_repr_lists = []
    print( "Data on transmitter side is -> " )
    for ( char , ascii ) in zip( input_chars , input_chars_ascii ):
        bin_repr = decimal_to_binary( ascii )
        bin_repr_lists.append( bin_repr )
        print( f"{char} -> {ascii} -> { list_to_str(bin_repr) }" )

    code_word_lists = []
    num_r_bits = None
    print( "Code words on transmitter side ->" ) 
    for ( char , bin_repr ) in zip( input_chars , bin_repr_lists ):
        code_word , num_r_bits = encode( bin_repr , parity )
        code_word_lists.append( code_word )
        print( f"{char} -> { list_to_str(code_word) }" )

    print( "Number of redundant bits => r = " , num_r_bits )
    print( "Number of bits in message => m = " , len( code_word_lists[0] ) - num_r_bits )

    print( "---------- Channel / Transmission Medium -----------" )

    error = input( "Do you wish to induce errors in the message? ([no],yes) => " ) 
    if error == "yes":
        for code_word in code_word_lists:
            random_position = random.randint( 0 , len( code_word ) - 1 ) 
            code_word[ random_position ] = 0 if code_word[random_position] == 1 else 1
            print( "For code word {}, error induced at position={}".format( list_to_str(code_word) , random_position ) )

    print( "---------- Receiver -----------" )

    decoded_message: str = ""
    for code_word in code_word_lists:
        code_word_str = list_to_str( code_word )
        parity_bits = decode( code_word , num_r_bits , parity="even" )

        if sum( parity_bits ) == 0:
            parity_positions = [ 2**i - 1 for i in range(num_r_bits) ]
            char_bin_repr = [ c for (pos , c) in enumerate(code_word) if pos not in parity_positions ]
            char = chr(binary_to_decimal( char_bin_repr )) 
            print( f"Code {code_word_str} received without any error." , 
                  f"Decoded character => { char }" )
        else:
            error_position = binary_to_decimal( parity_bits[::-1] ) - 1
            print( f"Code {code_word_str} received with any error." , 
                  f"Error is at index={ error_position }"
                   )
            code_word[error_position] = 0 if code_word[error_position] == 1 else 1
            parity_positions = [ 2**i - 1 for i in range(num_r_bits) ]
            char_bin_repr = [ c for (pos , c) in enumerate(code_word) if pos not in parity_positions ]
            char = chr(binary_to_decimal( char_bin_repr )) 
            print( f"Decoded character after correcting error => {char}" )
        decoded_message += char
    
    print( "Message on receiver side =>" , decoded_message )