
class Percentages:

    def __init__(self):
        self.percentages = []

    def add_percentage( self , percent ):
        self.percentages.append( percent )

    def quick_sort( self ):
        self.quick_sort_param( self.percentages )

    def quick_sort_param( self , arr ):
        pass

    def rearrange( self , arr , initial_index , pivot_index ):
        pivot = arr[ pivot_index ]
        left_pointer = initial_index
        for i in range( initial_index , pivot_index ):
            if arr[ i ] < pivot:
                self.swap( arr , initial_index , i )
                initial_index += 1



    def swap( self , arr , a1 , a2 ):
        arr[a1], arr[a2] = arr[a2], arr[a1]

    def get_top_k( self , k ):
        return self.percentages[ -1 : - k - 1: -1 ]

