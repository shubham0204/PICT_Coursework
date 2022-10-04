"""
Name: Shubham Panchal
Roll number: 21356

"""
from marks import Marks

while True:
    database = Marks()
    N = int( input( "Enter number of students : " ) )
    for i in range( N ):
        database.add_marks( int( input( "Enter marks for student {} : ".format( i + 1 ) ) ) )

    choice = int( input( """
        Enter choice for sorting ->
        1 : Insertion Sort
        2 : Shell Sort
        Any other char -> Exit
    """))

    if choice == 1:
        database.insertion_sort()
    elif choice == 2:
        database.shell_sort()
    else:
        break
    print( "Sorted array : " , database.marks )
    print( "Top 5 : " , database.get_top_k( 5 ) )