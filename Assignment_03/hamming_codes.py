import random

def decimal_to_binary( x: int ) -> str:
    p = x
    output = ""
    while p != 0:
        m = p // 2
        output += str(p % 2)
        p = m
    return output[::-1]

def get_even_parity( seq: list[int] ) -> int:
    return int( sum(seq) % 2 != 0 )

def get_odd_parity( seq: list[int] ) -> int:
    return int( sum(seq) % 2 == 0 )

def encode( message: str , parity: str ) -> tuple[ str , int ]:
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
        parity_seq = []
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

    code_word = "".join( [ str(bit) for bit in code_word ] )
    return code_word , r

def decode( code_word: str , r: int , parity: str ) -> dict[ str , int ]:
    parity_func = get_even_parity if parity == "even" else get_odd_parity

    parity_positions = [ 2**i - 1 for i in range(r) ]
    parity_bits: dict[ str , int ] = {}
    for i , pos in enumerate( parity_positions ):
        parity_seq = []
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
        parity_bits[ f"p_{2**i}"] = parity_func( parity_seq )

    return parity_bits
    
parity = "even"

input_message_str = input( "Enter message: " )
input_characters = list( input_message_str )
input_chars_ascii = [ ord( c ) for c in input_characters ]

bin_strings = []
print( "Data on transmitter side is -> " )
for ( char , ascii ) in zip( input_characters , input_chars_ascii ):
    bin_str = decimal_to_binary( ascii )
    bin_strings.append( bin_str )
    print( f"{char} -> {ascii} -> {bin_str}" )

code_words = []
num_r_bits = None
print( "Code words on transmitter side ->" ) 
for ( char , bin_str ) in zip( input_characters , bin_strings ):
    code_word , num_r_bits = encode( bin_str , parity )
    code_words.append( code_word )
    print( f"{char} -> {code_word}" )

print( "Number of redundant bits => r = " , num_r_bits )
print( "Number of bits in message => m = " , len( code_words[0] ) - num_r_bits )

error = input( "Do you wish to induce errors in the message? ([no],yes)" ) 
if error == "yes":
    num_errors = int( input( "How many bits should be flipped randomly in the message?" ) )
    random_positions = [ random.randint( 0 , len( code_word[0] ) - 1 ) for _ in range( num_errors ) ]
    flip_bit = lambda bit: int( not bool(bit))
