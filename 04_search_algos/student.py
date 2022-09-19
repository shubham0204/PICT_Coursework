"""
Name: Shubham Panchal
Roll number: 21356

a) Write a Python program to store roll numbers of student in
array who attended training program in random order. Write
function for searching whether particular student attended
training program or not, using Linear search and Sentinel
search.
b) Write a Python program to store roll numbers of student
array who attended training program in sorted order. Write
function for searching whether particular student attended
training program or not, using Binary search and Fibonacci
search.
"""

class StudentData:

    def __init__(self):
        self.students = []
        self.num_students = 0

    def add_student( self , student ):
        self.students.append( student )
        self.num_students += 1

    def display(self):
        for student in self.students:
            print( student )

    def populate( self , N ):
        for i in range( N ):
            self.add_student( Student( f'person{i+1}' , i+1 ) )

    def clear(self):
        self.num_students = 0
        self.students = []

    def search_linear( self , student ):
        i = 0
        while True:
            if i < self.num_students:
                if self.students[ i ] == student:
                    return i
                i += 1
            else:
                break
        return -1

    def search_sentinel( self , student ):
        i = 0
        # Setting the sentinel
        students_with_sentinel = self.students
        students_with_sentinel[ self.num_students - 1 ] = student
        while True:
            # Assertion i < self.num_students is eliminated
            if students_with_sentinel[ i ] == student:
                return i
            i += 1

    def search_fibonacci( self , student ):
        f0 = 0
        f1 = 1
        f2 = f1 + f0
        # Compute fibonacci number that is greater than or equal to size of the given array
        length = len( self.students )
        while f2 <= length:
            f0 = f1
            f1 = f2
            f2 = f1 + f0
        offset = -1
        while f0 >= 0:
            index = min(f0 + offset, length - 1)
            if self.students[index].rollnumber < student.rollnumber:
                f2 = f1
                f1 = f0
                f0 = f2 - f1  # f2 = f0 + f1
                offset = index
            elif self.students[index].rollnumber > student.rollnumber:
                f2 = f0
                f1 = f1 - f2
                f0 = f2 - f1
            else:
                result = index - 1
                break
        else:
            result = -1
        return result

    def search_binary( self , student ):
        key = student.rollnumber
        L = 0
        R = len( self.students ) - 1
        while L <= R:
            mid = ( L + R ) // 2
            if self.students[ mid ].rollnumber < key:
                L = mid + 1
            elif self.students[ mid ].rollnumber > key:
                R = mid - 1
            else:
                return mid
        else:
            return -1


class Student:

    def __init__( self , name , rollnumber ):
        self.name = name
        self.rollnumber = rollnumber

    def __eq__(self, other):
        return self.rollnumber == other.rollnumber

    def __str__(self):
        return f"{self.rollnumber} {self.name}"

    @staticmethod
    def create_student():
        name = input( 'Enter name for student : ' )
        number = int( input( 'Enter {}\'s roll number : '.format( name ) ) )
        return Student( name , number )
