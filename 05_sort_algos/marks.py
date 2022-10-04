
class Marks:

    def __init__(self):
        self.marks = []

    def add_marks( self , marks ):
        self.marks.append( marks )

    def insertion_sort( self ):
        # Iterate through each element
        for i in range( len( self.marks ) ):
            # Iterating backwards from current element : i -> 1
            for j in range( i , 0 , -1 ):
                # if jth element is smaller than ( j - 1 )th element, swap them
                if self.marks[ j ] < self.marks[ j - 1 ]:
                    self.swap( j , j - 1 )

    def swap( self , a1 , a2 ):
        self.marks[a1], self.marks[a2] = self.marks[a2], self.marks[a1]

    def shell_sort( self ):
        N = len( self.marks )
        # Partitions are a geometric progression
        interval = N // 2
        while interval > 0:
            # Iterate from interval -> last element
            for i in range(interval, N):
                # Backward sorting with gaps of `interval` ( similar to insertion sort )
                for j in range( i , interval - 1 , -interval ):
                    if self.marks[ j ] < self.marks[ j - interval ]:
                        self.swap( j - interval , j )
            interval //= 2

    def get_top_k( self , k ):
        return self.marks[ -1 : - k - 1: -1 ]

