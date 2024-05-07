"""
N-queens as a CSP (Constraint Satisfaction Problem)
and solving it with backtracking
Backtracking: DFS + Pruning

With backtracking
* The search space is can be very large
* It is an exhaustive search
* Worst case complexity is exponential

References:
https://www.cs.toronto.edu/~fbacchus/Presentations/CSP-BasicIntro.pdf
https://www.cs.auckland.ac.nz/courses/compsci369s1c/lectures/GG-notes/CS369-Backtrack-BB.pdf
"""


# Check if no queens are crossing each other
# given the queen is present at (row,col) in config
def validate_config(config: list[list[int]], row: int, col: int) -> bool:
    global N
    # Check along horizontal axis
    x = 0
    while x < col:
        if config[row][x] == 1:
            return False
        x += 1
    # Check diagonally going towards top-left
    x, y = row, col
    while x >= 0 and y >= 0:
        if config[x][y] == 1:
            return False
        x -= 1
        y -= 1
    # Check diagonally going towards bottom-right
    x, y = row, col
    while x < N and y >= 0:
        if config[x][y] == 1:
            return False
        x += 1
        y -= 1
    return True


def print_board(board: list[list[int]]):
    for row in board:
        print(row)
    print("===" * 6)


def solve_n_queens(config: list[int], col: int) -> bool:
    global N

    if col == N:
        # The CSP was solved for all variables
        # indicating a success
        print_board(config)
        return True

    # The variables of the CSP have been partially assigned
    # Assigned variables => [ X_1 , X_2 , ... , X_{col-1} ]
    # Now, assign values to X_col
    for i in range(N):
        # Check if [ X_1 , X_2 , ... , X_{col}=i ] is
        # a valid configuration for the problem
        if validate_config(config, i, col):
            # if valid, place a queen at (i,config)
            # and repeat the entire process for a partial assignment of
            # [ X_1 , X_2 , ... , X_col ]
            config[i][col] = 1
            if solve_n_queens(config, col + 1):
                # if a valid solution is received from the
                # lower/future assignments, return positive feedback
                # from this assignment to the upper/prior assignments
                return True

            # if we report a dead-end in lower/future assignments (invalid config)
            # remove the queen from (i,col) from this assignment
            # and continue for the next assignment in the loop
            config[i][col] = 0
    return False


# CSP definition -> ( X , D , C )
# X -> ( X_1 , X_2 , ... , X_N )  => Variables
# D -> ( D_1 , D_2 , ... , D_N )  => Domains of variables
# C -> Constraints on variables

# Size of the chess board
# also, the number of variables in the CSP
N = int(input("Enter value of N: "))

# Initial configuration
# A N * N 2D array with all zeros
config = [[0 for _ in range(N)] for _ in range(N)]

if solve_n_queens(config, 0):
    print(f"{N} queens solved")
else:
    print(f"{N} queens could not be solved")
