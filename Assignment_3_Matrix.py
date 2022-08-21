
class Matrix:

    def __init__( self , m , n , name ):
        self.__m = m
        self.__n = n
        self.__name = name
        print( f'Enter values for matrix {name}:' )
        matrix = []
        for i in range( m ):
            row = []
            for j in range( n ):
                value = input( f'Enter value for {i+1},{j+1} : ' )
                row.append( value )
            matrix.append( row )
        print( f'Matrix {name} initialized' )

    def shape(self):
        return self.__m , self.__n

    def __add__(self, other ):
        assert self.shape() == other.shape() , "Matrices must have the same dimensions for addition"
