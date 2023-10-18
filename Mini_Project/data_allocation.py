from routines import to_sql_tuple
import random

NUM_TEAMS = 10
NUM_JUDGES = 10
NUM_ALLOCATIONS = 40

for _ in range( NUM_ALLOCATIONS ):
    print( to_sql_tuple( str(random.randint( 1 , NUM_JUDGES )) , str(random.randint( 1 , NUM_TEAMS )) ) + "," )
