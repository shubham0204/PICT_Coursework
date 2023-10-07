from routines import *

N = 10
for _ in range( N ):
    print( to_sql_tuple( 
        to_sql_string( get_random_team_name() ) , 
        to_sql_string( "<sample-abstract>" ) ,
        to_sql_string( get_random_domain() ) , 
        to_sql_string( "SOFTWARE" ) ,
        to_sql_string( get_random_room() ) ,
        to_sql_string( get_random_institute() ) 
    ) + " ," )
