
# Import all the `operations.py` module
from operations import *

# Printing basic info about the program
print(
"""
The following operations ( options for <operation> ) are available in this calculator program:
1. Addition -> '+'
2. Subtraction -> '-'
3. Multiplication -> '*'
4. Division -> '/'
5. Exponentiation -> '^'
6. Floor Division -> '//'
7. Remainder -> '%'

Follow the general pattern: '<operand_1> <operation> <operand_2>'

"""
)

# Taking input from the user
user_input = input( 'Enter the command : ' )

# Split the `user_input` to parse operand_1, op and operand_2
values = user_input.split()
x = float( values[ 0 ] )
op = values[ 1 ]
y = float( values[ 2 ] )

# A mapping from string `op` to a function that performs the operation
# In Python, functions are treated as objects
ops_to_func_map = {
    '+' : add ,
    '-' : subtract ,
    '*' : multiply ,
    '/' : divide ,
    '//' : floor_divide ,
    '^' : power ,
    '%' : remainder
}

func = ops_to_func_map.get( op )
if func is not None:
    # If an available function is chosen, call that function with `x` and `y`
    output = func( x , y )
    print( 'Output of {} is {}'.format( user_input , output ) )
else:
    print( 'Choose a valid operation')



