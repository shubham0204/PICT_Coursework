"""
N-queens as a CSP (Constraint Satisfaction Problem)
and solving it with branch-and-bound
References:
https://www.cs.toronto.edu/~fbacchus/Presentations/CSP-BasicIntro.pdf
https://www.cs.auckland.ac.nz/courses/compsci369s1c/lectures/GG-notes/CS369-Backtrack-BB.pdf
https://www.geeksforgeeks.org/8-queen-problem/
https://crystal.uta.edu/~kumar/CSE5311_10FLDAA/CSE5311M_BT_BB.pdf

Branch and bound technique
* Limits the search space
* Through an estimate of the
* Upper bound or Lower bound
"""

N = 4

# Initial configuration
config = [[0 for _ in range(N)] for _ in range(N)]


def validate_config(config: list[list[int]], row: int, col: int) -> bool:
    # Check along horizontal axis
    for x in range(col):
        if config[row][x] == 1:
            return False
    # Check diagonally from upper-left
    for x, y in zip(range(row, -1, -1), range(col, -1, -1)):
        if config[x][y] == 1:
            return False
    # Check diagonally from bottom-left
    for x, y in zip(range(row, N, 1), range(col, -1, -1)):
        if config[x][y] == 1:
            return False
    return True


def print_board(board: list[list[int]]):
    for row in board:
        print(row)
    print("===" * 6)
