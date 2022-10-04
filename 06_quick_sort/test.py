from percentages import Percentages
from measure_time import measure_execution_time

percentages = Percentages()

# Worst-case scenario
# Elements are in descending order
input_array = []
N = 200
for i in range( N , 0 , -1 ):
    input_array.append( i )

time_ns = measure_execution_time( percentages.quick_sort_param , ( input_array , 0 , len( input_array ) - 1 ) )
time_ms = time_ns / ( 10**6 )
print( time_ms )