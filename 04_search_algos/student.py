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
        self.rollnumbers = []
        self.num_students = 0

    def add_student( self , student ):
        self.rollnumbers.append( student )
        self.num_students += 1

    def display(self):
        for student in self.rollnumbers:
            print( student )

    def populate( self , N ):
        for i in range( N ):
            self.add_student( i + 1 )

    def clear(self):
        self.num_students = 0
        self.rollnumbers = []

    def selection_sort(self):
        for i in range( self.num_students ):
            min_student = self.rollnumbers[ i ]
            min_student_index = i
            for j in range( i + 1 , self.num_students ):
                if self.rollnumbers[ j ] < min_student:
                    min_student = self.rollnumbers[ j ]
                    min_student_index = j
            self.swap( i , min_student_index )

    def swap(self , k1 , k2 ):
        self.rollnumbers[ k1 ] , self.rollnumbers[ k2 ] = self.rollnumbers[ k2 ] , self.rollnumbers[ k1 ]


    def search_linear( self , student ):
        i = 0
        while True:
            if i < self.num_students:
                if self.rollnumbers[ i ] == student:
                    return i
                i += 1
            else:
                break
        return -1

    def search_sentinel( self , student ):
        i = 0
        # Setting the sentinel
        students_with_sentinel = self.rollnumbers
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
        length = len( self.rollnumbers )
        while f2 <= length:
            f0 = f1
            f1 = f2
            f2 = f1 + f0
        offset = -1
        key = student
        while f0 >= 0:
            index = min(f0 + offset, length - 1)
            if self.rollnumbers[index] < key:
                # Previous set of fibonacci numbers
                f2 = f1
                f1 = f0
                f0 = f2 - f1  # f2 = f0 + f1
                offset = index
            elif self.rollnumbers[index] > key:
                # Previous two sets of fibonacci numbers
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
        key = student
        L = 0
        R = len( self.rollnumbers ) - 1
        while L <= R:
            mid = ( L + R ) // 2
            if self.rollnumbers[ mid ] < key:
                L = mid + 1
            elif self.rollnumbers[ mid ] > key:
                R = mid - 1
            else:
                return mid
        else:
            return -1

