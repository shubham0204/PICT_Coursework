"""
Name: Shubham Panchal
Roll no: 21356

Problem Statement:
In second year computer engineering class, group A student’s play cricket,
 group B students play badminton and group C students play football.
 Write a Python program using functions to compute following: -
 a) List of students who play both cricket and badminton
 b) List of students who play either cricket or badminton but not both
 c) Number of students who play neither cricket nor badminton
 d) Number of students who play cricket and football but not badminton.
(Note- While realizing the group, duplicate entries should be avoided, Do not use SET built-in functions)
"""

class Set:

    # Constructor of the class
    # elements -
    def __init__( self , elements ):
        self.elements = self.unique( elements )

    def union( self, other ):
        """
        Computes union of `self` and `other`
        """
        union_elements = self.concatenate( self.elements , other.elements )
        return Set( elements=union_elements )


    def intersection(self, other ):
        """
        Computes intersection of `self` and `other`
        """
        intersection_elements = []
        for element in other.elements:
            if element in self.elements and element in other.elements:
                intersection_elements.append( element )
        return Set( elements=intersection_elements )

    def difference(self, other):
        """
        Computes difference between `self` and `other`
        """
        difference_elements = []
        for element in self.elements:
            if not self.check_in( element , other.elements ) and not self.check_in( difference_elements , element ):
                difference_elements.append( element )
        return Set( elements=difference_elements )

    def complement( self , super_set ):
        """
        Computes complement of `self` given the superset
        """
        return super_set.difference( self )

    def concatenate( self , x , y ):
        """
        Concatenates two lists
        """
        concat = x
        for element in y:
            concat.append( element )
        return concat

    def unique(self , elements):
        """
        Filter out unique items from `elements`
        :param elements:
        :return:
        """
        output = []
        for element in elements:
            if not self.check_in( element , output ):
                output.append( element )
        return output

    def check_in(self , x , element ):
        """
        Check if `element` is present in `x`
        """
        for y in element:
            if x == y:
                return True
        return False

    def __str__(self):
        return str( self.elements )


def take_input( set_name ):
    N = int( input( 'Enter number of students for {} : '.format( set_name ) ) )
    members = []
    for i in range( N ):
        member = input( 'Enter member {} for {} : '.format( i + 1 , set_name ) )
        if member not in members:
            members.append( member )
        else:
            print( 'Duplicate member found' )
            continue
    return Set( members )

# User input
cricket = take_input( 'cricket' )
badminton = take_input( 'badminton' )
football = take_input( 'football' )
no_sport = take_input( 'students playing no sport ' )


# 1 - C intersection B
cricket_and_badminton = cricket.intersection( badminton )
print( "Students playing cricket and badminton" )
print( cricket_and_badminton )

# 2 - ( C union B ) - ( C intersection B )
union = cricket.union( badminton )
cricket_or_badminton_not_both = union.difference( cricket_and_badminton )
print( "Students playing cricket or badminton but not both")
print( cricket_or_badminton_not_both )

# 3 - ( C union B )^C
super_set = cricket.union( badminton ).union( football ).union( no_sport )
neither_cricket_nor_badminton = union.complement( super_set )
print( 'Students playing neither cricket nor badminton' )
print( neither_cricket_nor_badminton )

# 4 - ( C intersection F ) - B
cricket_and_football = cricket.intersection( football )
cricket_and_football_not_badmton = cricket_and_football.difference( badminton )
print( "Students playing cricket and football not badminton" )
print( cricket_and_football_not_badmton )
