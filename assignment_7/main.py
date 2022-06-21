
user_input_1 = input( 'Enter a phrase 1 : ' )
user_input_2 = input( 'Enter a phrase 2 : ' )
substring = input( 'Enter a substring to search : ' )

# Use the builtin function `len` as `str` object is iterable
length = len( user_input_1 )
print( 'Length of phrase 1 is {}'.format( length ) )

# Reverse the given string
reverse = reversed( user_input_1 )
print( 'Reverse of phrase 1 is ' , reverse )

# Check if phrase_1 and phrase_2 are equal
are_equal = user_input_1 == user_input_2
if are_equal:
    print( 'Both phrases are equal' )
else:
    print( 'Both phrases are not equal' )

