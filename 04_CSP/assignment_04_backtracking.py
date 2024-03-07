"""
N-queens as a CSP (Constraint Satisfaction Problem)
and solving it with backtracking
References: 
https://www.cs.toronto.edu/~fbacchus/Presentations/CSP-BasicIntro.pdf
https://www.cs.auckland.ac.nz/courses/compsci369s1c/lectures/GG-notes/CS369-Backtrack-BB.pdf

With backtracking
* The search space is can be very large
* It is an exhaustive search
* Worst case complexity is exponential
"""

N = 4

# Initial configuration
config = [ [ 0 for _ in range(N) ] for _ in range(N) ]

def validate_config(
    config: list[list[int]] , 
    row: int , 
    col: int
) -> bool:
    # Check along horizontal axis
    for x in range( col ):
        if config[ row ][ x ] == 1:
            return False
    # Check diagonally from upper-left
    for ( x , y ) in zip( range( row , -1 , -1 ) , range( col , -1 , -1 ) ):
        if config[ x ][ y ] == 1:
            return False
     # Check diagonally from bottom-left
    for ( x , y ) in zip( range( row , N , 1 ) , range( col , -1 , -1 ) ):
        if config[ x ][ y ] == 1:
            return False
    return True

def print_board(
    board: list[list[int]]
):
    for row in board:
        print( row )
    print( "===" * 6 )
    

def solve_n_queens( 
    config: list[int] , 
    col: int
) -> bool:
    if col == N:
        print_board( config )
        return True
    for i in range( N ):
        if validate_config( config , i , col ):
            config[ i ][ col ] = 1
            if solve_n_queens( config , col + 1 ):
                return True
            config[ i ][ col ] = 0
    return False

res = solve_n_queens( config , 0 )
print( res )