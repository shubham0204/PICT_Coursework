
class Percentages:

    def __init__(self):
        self.percentages = []

    def add_percentage( self , percent ):
        self.percentages.append( percent )

    def quick_sort( self ):
        self.quick_sort_param( self.percentages , 0 , len( self.percentages - 1 )  )

    def quick_sort_param( self , arr , low , high ):
        if low < high:
            pi = self.__partition( arr , low , high )
            # Partition left of pivot
            self.quick_sort_param( arr , low, pi - 1 )
            # Partition right of pivot
            self.quick_sort_param( arr , pi + 1, high )

    def __partition( self , arr , low , high ):
        pivot = arr[ high ]
        i = low - 1
        # Iterate from left to right, excluding the pivot
        for j in range( low , high ):
            # If element is smaller than pivot, send it back
            if arr[ j ] <= pivot:
                i += 1
                arr[ i ], arr[ j ] = arr[ j ], arr[ i ]

        # Place pivot element at i + 1 position
        arr[ high ], arr[ i + 1 ] = arr[ i + 1 ], arr[ high ]

        # Return position of pivot
        return i + 1

    def get_top_k( self , k ):
        return self.percentages[ -1 : - k - 1: -1 ]

