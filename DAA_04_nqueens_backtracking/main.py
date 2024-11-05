import copy

"""
Board representation:
[X_0, X_1, X_2, ..., X_{N-1}]
X_i represents the row where the queen is placed in the ith row
X_i = -1 indicates no queen has been placed yet

Initial board configuration:
[-1 -1 -1 ... -1]
"""


def validate_board(board, i, X_i):
    for j in range(i):
        if board[j] == X_i or abs(board[j] - X_i) == abs(j - i):
            return False
    return True


def print_board(board):
    global N
    board_2d = [[" . " for _ in range(N)] for _ in range(N)]
    for i in range(N):
        if board[i] != -1:
            board_2d[i][board[i]] = " Q "
    for row in board_2d:
        print(" ".join(row))


def solve_n_queens(board, i):
    global N
    if i == N:
        print("solved")
        print_board(board)
        return True
    for X_i in range(N):
        if validate_board(board, i, X_i):
            child_board = copy.deepcopy(board)
            board[i] = X_i
            if solve_n_queens(board, i + 1):
                return True
    return False


N = 4
board = [-1 for _ in range(N)]
solve_n_queens(board, 0)
