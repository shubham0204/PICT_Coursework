from routines import *
import random

N = 50
for _ in range( N ):
    print( to_sql_tuple( 
        to_sql_string( get_random_name() ) , 
        str( random.randint( 1 , 10 ) ) ,
        to_sql_string( get_random_contact_number() )
    ) + " ," )
