"""
Problem Statement

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
    """
    Custom implementation of a set and operations associated with it.
    """

    def __init__( self , elements , name='set' ):
        """
        Constructor of the class `Set`
        :param elements: Elements that the set should contain on initialization. Note, these elements should be
        unique.
        :param name: The name of this set. Default value is `set`
        """
        self.elements : list = elements
        self.name : str = name

    def __add__( self, other ):
        """
        Overriding the '+' operator that would compute the union of `self` and `other` which are instances of the
        class `Set`
        :param other: The operand with whom the union is computed
        :return: The union of the two sets
        """
        union_elements = []
        for element in self.elements + other.elements:
            if element not in union_elements:
                union_elements.append( element )
        return Set( union_elements )

    def __mul__(self, other ):
        """
        Overriding the '*' operator that would compute the intersection of `self` and `other` which are instances of the
        class `Set`
        :param other: The operand with whom the intersection is computed
        :return: The intersection of the two sets
        """
        intersection_elements = []
        for element in other.elements:
            if element in self.elements and element in other.elements and element not in intersection_elements:
                intersection_elements.append( element )
        return Set( intersection_elements )

    def __sub__(self, other):
        """
        Overriding the '-' operator that would compute the difference of `self` and `other` which are instances of the
        class `Set`
        :param other: The operand with whom the difference is computed
        :return: The difference of the two sets
        """
        difference_elements = self.elements
        for element in other.elements:
            if element in self.elements and element not in difference_elements:
                difference_elements.remove( element )
        return Set( difference_elements )

    # Method to compute the complement of this set, given a parent/super-set
    def complement( self , super_set ):
        complement_elements = []
        for element in super_set.elements:
            if element not in self.elements and element not in complement_elements:
                complement_elements.append( element )
        return Set( complement_elements )

    # This method will be called when print( Set ) is used
    def __str__(self):
        return f"{self.name}: {self.elements}"

    def __iter__(self):
        return self.elements


cricket = Set( [ 'p1' , 'p2' ] , name='C' )
badminton = Set( ['p3' , 'p2' , 'p1'] , name='B' )
football = Set( [ 'p5' , 'p2' , 'p6' ] , name='F' )

super_set = cricket + badminton + football
super_set.name = "all_students"

# Students playing both cricket and badminton -> C intersection B
cricket_and_badminton = cricket * badminton
print( 'Students playing both cricket and badminton' , cricket_and_badminton )

# Students playing either cricket or badminton -> (C union B) - (C intersection B)
cricket_or_badminton = cricket + badminton
either_cricket_or_badminton = cricket_or_badminton - cricket_and_badminton
print( 'Students playing either cricket or badminton' , either_cricket_or_badminton )

# Students playing neither cricket nor badminton -> (superset) - (C union B)
neither_cricket_nor_badminton = cricket_or_badminton.complement( super_set )
print( 'Students playing neither cricket nor badminton' , neither_cricket_nor_badminton )

cricket_football_not_badmton = ( cricket * football ) * ( badminton.complement( super_set ) )
print( 'Students playing cricket and football but not badminton' , neither_cricket_nor_badminton )





