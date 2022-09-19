"""
Name: Shubham Panchal
Roll no: 21356

Problem Statement:
Write a python program to compute following computation on
matrix:
a) Addition of two matrices
b) Subtraction of two matrices
c) Multiplication of two matrices
d) Transpose of a matrix
"""

class Matrix:

    def __init__( self , shape , elements=None , name='matrix' ):
        """
        Constructor of the class `Matrix`
        Given the shape ( m , n ), if the element are not provided, a zero matrix
        is initialized
        """
        self.m = shape[0] # Num rows
        self.n = shape[1] # Num columns
        self.name = name
        self.elements = []
        if elements is None:
            self.initialize()
        else:
            self.elements = elements

    def initialize(self):
        """
        Initialize the m * n matrix with zeros
        """
        for i in range( self.m ):
            row = []
            for j in range( self.n ):
                row.append( 0.0 )
            self.elements.append( row )

    def input( self ):
        """
        Take elements of the matrix as input from the user
        """
        for i in range( self.m ):
            for j in range( self.n ):
                element = input( 'Enter element at ( {} , {} ): '.format( i + 1 , j + 1 ) )
                element = int( element )
                self.elements[ i ][ j ] = element

    def get_element( self , i , j ):
        """
        Get the ( ith , jth ) element of this matrix
        """
        return self.elements[ i ][ j ]

    def set_element( self , i , j , element ):
        """
        Set the value of ( ith , jth ) element in this matrix
        """
        self.elements[ i ][ j ] = element

    def shape(self):
        """
        Return the dimensions of this matrix : ( m , n )
        """
        return ( self.m , self.n )

    def get_row( self , i ):
        """
        Get the ith row from this matrix
        """
        return self.elements[ i ]

    def get_column( self , j ):
        column = []
        for k in range( self.m ):
            column.append( self.get_element( k , j ))
        return column

    def add( self , other ):
        """
        Perform addition of this matrix and `other`
        The shapes of the matrices should be the same for addition
        """
        if self.shape() == other.shape():
            output_elements = []
            for i in range( self.m ):
                row = []
                for j in range( self.n ):
                    row.append( self.get_element( i , j ) + other.get_element( i , j ) )
                output_elements.append( row )
            return Matrix( self.shape() , output_elements )
        else:
            print( 'Matrix addition is not possible with different shapes' )

    def subtract( self , other ):
        """
        Perform subtraction on this matrix and `other`
        The shapes of the matrices should be the same for addition
        """
        if self.shape() == other.shape():
            output_elements = []
            for i in range( self.m ):
                row = []
                for j in range( self.n ):
                    row.append( self.get_element( i , j ) - other.get_element( i , j ) )
                output_elements.append( row )
            return Matrix( self.shape() , output_elements )
        else:
            print( 'Matrix subtraction is not possible with different shapes' )

    def dot_product( self , x , y ):
        """
        Computes the sum: x_i * y_i
        """
        prod = 0
        i = 0
        for xi in x:
            prod += xi * y[ i ]
            i += 1
        return prod

    def multiply( self , other ):
        """
        Perform matrix multiplication of this matrix and `other`
        If the shape of this matrix is ( m , n ) then the shape of `other` must be ( n , p )
        The shape of the resulting product is ( m , p )
        """
        if self.shape()[1] == other.shape()[0]:
            prod_shape = ( self.shape()[0] , other.shape()[1] )
            output_elements = []
            for i in range( prod_shape[0] ):
                row = []
                for j in range( prod_shape[1] ):
                    row.append( self.dot_product( self.get_row( i ) , other.get_column( j ) ) )
                output_elements.append( row )
            return Matrix( prod_shape , output_elements )
        else:
            print( 'Matrix multiplication is not possible with the given shapes' )

    def transpose( self ):
        """
        Computes transpose of this matrix
        """
        output = Matrix( shape=( self.n , self.m ) )
        for i in range( self.n ):
            for j in range( self.m ):
                output.set_element( i , j , self.get_element( j , i ) )
        return output

    def print(self):
        """
        Print this matrix in row-column representation
        """
        for i in range( self.m ):
            print( "|" , end=" " )
            for j in range( self.n ):
                print( self.get_element( i , j ) , end=" " )
            print( "|" )

while True:
    m1 = int( input( "Enter no. of rows for 1st matrix : " ) )
    n1 = int( input( "Enter no. of columns for 1st matrix : " ) )
    m2 = int( input( "Enter no. of rows for 2st matrix : " ) )
    n2 = int( input( "Enter no. of columns for 2st matrix : " ) )

    print( 'Enter values for 1st matrix -> ')
    m1 = Matrix( ( m1 , n1 ) )
    m1.input()

    print( 'Enter values for 2nd matrix -> ')
    m2 = Matrix( ( m2 , n2 ) )
    m2.input()

    print( '1st matrix is -> ' )
    m1.print()

    print( '2nd matrix is -> ' )
    m2.print()

    print( 'Sum of both matrices -> ' )
    sum = m1.add( m2 )
    if sum is not None:
        sum.print()

    print( 'Difference between both matrices -> ' )
    diff = m1.subtract( m2 )
    if diff is not None:
        diff.print()

    print( 'Product of the matrices -> ' )
    prod = m1.multiply( m2 )
    if prod is not None:
        prod.print()

    print( 'Transpose of 1st matrix -> ' )
    m1.transpose().print()

    print( 'Transpose of 2st matrix -> ' )
    m2.transpose().print()




