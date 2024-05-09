import copy
from heapq import heappush , heappop

class Puzzle:

    def __init__( self , elements ):
        for i in range( len( elements ) ):
            for j in range( len( elements ) ):
                if elements[i][j] == 0:
                    self.pos = (i,j)
                    break
        self.n_dims = len( elements )
        self.board = elements

    def print( self ):
        for row in self.board:
            print( row if row != 0 else "*" )

def heuristic( curr_puzzle: Puzzle , goal_puzzle: Puzzle ):
    h = 0
    for i in range( curr_puzzle.n_dims ):
        for j in range( curr_puzzle.n_dims ):
            if curr_puzzle.board[i][j] != goal_puzzle.board[i][j]:
                h += 1
    return h

def goal_test( curr_puzzle: Puzzle , goal_puzzle: Puzzle ):
    for i in range( curr_puzzle.n_dims ):
        for j in range( curr_puzzle.n_dims ):
            if curr_puzzle.board[i][j] != goal_puzzle.board[i][j]:
                return False
    return True

def move( curr_puzzle: Puzzle ) -> list[Puzzle]:
    x , y = curr_puzzle.pos
    dim = curr_puzzle.n_dims
    possible_pos = []
    if x + 1 < dim and y < dim:
        possible_pos.append( (x+1,y) )
    if x < dim and y + 1 < dim:
        possible_pos.append( (x,y+1) )
    if x - 1 >= 0 and y >= 0:
        possible_pos.append( (x-1,y) )
    if x >= 0 and (y-1) >= 0:
        possible_pos.append( (x,y-1) )
    child_states = []
    for pos in possible_pos:
        child_board = copy.deepcopy(curr_puzzle.board)
        child_board[x][y] , child_board[pos[0]][pos[1]] = child_board[pos[0]][pos[1]] , child_board[x][y]
        child_states.append( Puzzle(child_board) )
    return child_states

def solve( init_puzzle , goal_puzzle ):
    open_set = [ init_puzzle ]
    g_score = { init_puzzle: 0 }
    f_score = { init_puzzle: heuristic(init_puzzle, goal_puzzle) }
    while len(open_set) != 0:
        min_f_score_node = min( open_set , key = lambda puzzle: f_score.get( puzzle , 1e10 ) )
        print(">> Selected state from frontier: ")
        curr_puzzle = min_f_score_node
        curr_puzzle.print()
        if goal_test(curr_puzzle, goal_puzzle):
            print("Done")
            break
        print(">> Possible states: ")
        open_set.remove(curr_puzzle)
        for child in move(curr_puzzle):
            tent_g_score = g_score.get( curr_puzzle , 1e10 ) + 1
            if tent_g_score < g_score.get( child , 1e10 ):
                g_score[child] = tent_g_score
                f_score[child] = tent_g_score + heuristic(child, goal_puzzle)
                if child not in open_set:
                    open_set.append(child)
                    child.print()
                    print(f"h(n) for above state is {heuristic(child, goal_puzzle)}")
                    print(f"g(n) for above state is {g_score[child]}")
                    print(f"f(n) for above state is {f_score[child]}")

    print("-----------------------------")


init_puzzle = Puzzle([[1, 2, 3], [0, 4, 6], [7, 5, 8]])
print("Initial state:")
init_puzzle.print()

goal_puzzle = Puzzle([[1, 2, 3], [4, 5, 6], [7, 8, 0]])
print("Goal state:")
goal_puzzle.print()

solve(init_puzzle, goal_puzzle)



