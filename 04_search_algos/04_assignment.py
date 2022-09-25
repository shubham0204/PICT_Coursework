
from student import StudentData

while True:
    database = StudentData()
    N = int( input( "Enter number of students : " ) )
    for i in range( N ):
        print( "For student {} ->".format( i + 1 ) )
        database.add_student( int( input( "Enter roll number : " ) ) )

    database.selection_sort()
    database.display()

    print( "For searching a student ...")
    search_student = int( input( "Enter roll number for searching : "))

    print(
        """
        Select a search algorithm
        1 -> Linear Search ( Sequential Search )
        2 -> Sentinel Search
        3 -> Fibonacci Search
        4 -> Binary Search
        To exit, enter 0
        """
    )
    option = int( input( "Enter a option : " ) )
    if option == 1:
        index = database.search_linear(search_student)
        print('Student found at index = ', index)
    elif option == 2:
        index = database.search_sentinel(search_student)
        print('Student found at index = ', index)
    elif option == 3:
        index = database.search_fibonacci(search_student)
        print('Student found at index = ', index)
    elif option == 4:
        index = database.search_binary(search_student)
        print('Student found at index = ', index)
    elif option == 0:
        print( 'Exiting ...')
        break