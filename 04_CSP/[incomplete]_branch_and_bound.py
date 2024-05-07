"""
N-queens as a CSP (Constraint Satisfaction Problem)
and solving it with branch-and-bound
Branch-and-Bound: BFS + Pruning

Branch and bound technique
* Limits the search space
* Through an estimate of the Upper bound or Lower bound

References:
https://www.cs.toronto.edu/~fbacchus/Presentations/CSP-BasicIntro.pdf
https://www.cs.auckland.ac.nz/courses/compsci369s1c/lectures/GG-notes/CS369-Backtrack-BB.pdf
https://crystal.uta.edu/~kumar/CSE5311_10FLDAA/CSE5311M_BT_BB.pdf
"""

N = 4

def get_num_crossing_queens(config: list[list[int]], i: int, j: int) -> int:
    num_crossing_queens = 0
    global N
    # Check along horizontal axis - forward
    b = j
    while b < N:
        if config[i][b] == 1:
            num_crossing_queens += 1
            break
        b += 1
    # Check along horizontal axis - backward
    b = j
    while b >= 0:
        if config[i][b] == 1:
            num_crossing_queens += 1
            break
        b -= 1
    # Check diagonally going upper-left
    a , b = i , j
    while a >= 0 and b >= 0:
        if config[a][b] == 1:
            num_crossing_queens += 1
            break
        a -= 1
        b -= 1
    # Check diagonally going upper-right
    a , b = i , j
    while a >= 0 and b < N:
        if config[a][b] == 1:
            num_crossing_queens += 1
            break
        a -= 1
        b += 1
    # Check diagonally going lower-left
    a , b = i , j
    while a < N and b >= 0:
        if config[a][b] == 1:
            num_crossing_queens += 1
            break
        a += 1
        b -= 1
    # Check diagonally going lower-right
    a , b = i , j
    while a < N and b < N:
        if config[a][b] == 1:
            num_crossing_queens += 1
            break
        a += 1
        b += 1
    return num_crossing_queens


def objective(config: list[list[int]]):
    h = 0
    for i in range( N ):
        col = [ config[j][i] for j in range(N) ]
        queen_index = col.index( 1 )
        config[ queen_index ][ i ] = 0
        h += get_num_crossing_queens(config, queen_index, i)
        config[ queen_index ][ i ] = 1
    return h

print( objective(
    [ 
        [ 0 , 1 , 1 , 1 ] , 
        [ 0 , 0 , 0 , 0 ] , 
        [ 1 , 0 , 0 , 0 ] , 
        [ 0 , 0 , 0 , 0 ] 
    ]
) )

def print_board(board: list[list[int]]):
    for row in board:
        print(row)
    print("===" * 6)


def solve_n_queens() -> bool:
    # Initial configuration
    config = [[0 for _ in range(N)] for _ in range(N)]
    for i in range( N ):
        config[ 0 ][ i ] = 1

    B = 1e10
    col = 0
    while col < N:
        h_min = 1e10
        h_min_i = 0
        for i in range(N):
            config[ i ][ col ] = 1
            print( config )
            h = objective(config)
            config[ i ][ col ] = 0
            print( h )
            if h < h_min:
                h_min = h
                h_min_i = i
        B = h_min
        config[ h_min_i ][ col ] = 1
        col += 1

    print( config )

solve_n_queens()

"""
# CSP definition -> ( X , D , C )
# X -> ( X_1 , X_2 , ... , X_N )  => Variables
# D -> ( D_1 , D_2 , ... , D_N )  => Domains of variables
# C -> Constraints on variables

# Size of the chess board
# also, the number of variables in the CSP
N = input("Enter value of N: ")

# Initial configuration
# A N * N 2D array with all zeros
config = [[0 for _ in range(N)] for _ in range(N)]

if solve_n_queens(config, 0):
    print(f"{N} queens solved")
else:
    print(f"{N} queens could not be solved")

"""