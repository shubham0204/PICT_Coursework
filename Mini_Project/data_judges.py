from routines import *

N = 10
for _ in range( N ):
    print( to_sql_tuple( 
        to_sql_string( get_random_name() ) , 
        to_sql_string( get_random_domain() ) ,
        to_sql_string( get_random_contact_number() )
    ) + " ," )

