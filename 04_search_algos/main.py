
from measure_time import measure_execution_time
from student import StudentData

database = StudentData()
database.populate( 100 )
#N = int( input( "Enter number of students : " ) )
#for i in range( N ):
#    print( "For student {} ->".format( i + 1 ) )
#    database.add_student( Student.create_student() )

# database.display()

print( "For searching a student ...")
search_student = int( input( "Enter roll number for searching : "))

index = database.search_linear( search_student )
print( index )
print( measure_execution_time( database.search_linear , ( search_student , ) ) )

index = database.search_sentinel( search_student )
print( index )
print( measure_execution_time( database.search_sentinel , ( search_student , ) ) )

index = database.search_fibonacci( search_student )
print( index )
print( measure_execution_time( database.search_fibonacci , ( search_student , ) ) )

index = database.search_binary( search_student )
print( index )
print( measure_execution_time( database.search_binary , ( search_student , ) ) )