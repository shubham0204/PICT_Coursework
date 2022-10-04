"""
Name: Shubham Panchal
Roll number: 21356

"""
from percentages import Percentages
from measure_time import measure_execution_time

while True:
    database = Percentages()
    N = int( input( "Enter number of students : " ) )
    for i in range( N ):
        database.add_percentage( int( input( "Enter percentage of student {} : ".format( i + 1 ) ) ) )

    database.quick_sort()
    print( "Sorted array : " , database.percentages )
    print( "Top 5 : " , database.get_top_k( 5 ) )