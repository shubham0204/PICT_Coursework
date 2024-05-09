from heapq import heappush , heappop
import copy

N = 3

def is_valid( board , row , col ):
    for i in range( row ):
        if board[i] == col or abs( board[i] - col ) == abs( i - row ):
            return False
    return True

def objective( board ):
    cost = 0
    for i in range(N):
        for j in range( i+1 , N):
            if board[i] == board[j] or abs( board[j] - board[i] ) == j - i:
                cost += 1
    return cost

def solve( initial_state ):

    board = [ -1 for _ in range(N) ] 
    queue = []

    heappush( queue , ( objective(board) , board ) )

    while len(queue) != 0:

        curr_node = heappop( queue )
        curr_board = curr_node[1]
        curr_cost = curr_node[0]

        row = 0
        while row < N and curr_board[row] != -1:
            row += 1

        if row == N:
            print( curr_board )
            return True

        for col in range(N):
            if is_valid(curr_board, row, col):
                new_board = copy.deepcopy(curr_board)
                new_board[row] = col
                print( new_board )
                new_cost = objective(new_board)
                heappush(queue, ( new_cost , new_board) )
    return False

print( solve( [ -1 for _ in range(N) ] ) )

