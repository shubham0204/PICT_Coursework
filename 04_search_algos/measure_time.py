
import time

def measure_execution_time( func , inputs , num_cycles=10000 ):
    times = []
    for _ in range( num_cycles ):
        t1 = time.time_ns()
        func( *inputs )
        times.append( time.time_ns() - t1 )
    return sum( times ) / len( times )
