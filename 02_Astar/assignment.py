import copy

INFINITY: int = 1e+10

class Puzzle:

    def __init__( 
        self , 
        elements: list[list[int]] , 
    ) -> None:
        assert( len( elements ) == len( elements[0] ) , "Puzzle must have equal rows and columns" )
        self.board = elements
        self.n_dims = len(elements)
        for i in range( self.n_dims ):
            for j in range( self.n_dims ):
                if self.board[i][j] == 0:
                    self.pos = ( i , j )
                    break

    def print( self ):
        for i in range( self.n_dims ):
            for j in range( self.n_dims ):
                print( self.board[i][j] , end=" " )
            print()

def move( puzzle: Puzzle ) -> list[Puzzle]:
    x , y = puzzle.pos[0] , puzzle.pos[1]
    dim = puzzle.n_dims 
    possible_pos: list[tuple[int,int]] = []
    if ( x + 1 ) < dim and y < dim:
        possible_pos.append( ( x + 1 , y ) )
    if x < dim and ( y + 1 ) < dim:
        possible_pos.append( ( x , y + 1) )
    if ( x - 1 ) >= 0 and y >= 0:
        possible_pos.append( ( x - 1 , y ) )
    if x >= 0 and ( y - 1 ) >= 0:
        possible_pos.append( ( x , y - 1 ) )
    new_states: list[Puzzle] = []
    for pos in possible_pos:
        pos_x , pos_y = pos[0] , pos[1]
        new_elements = copy.deepcopy( puzzle.board )
        new_elements[pos_x][pos_y] , new_elements[x][y] = new_elements[x][y] , new_elements[pos_x][pos_y]
        new_states.append( Puzzle( new_elements ) )
    return new_states

def heuristic( init_puzzle: Puzzle , goal_puzzle: Puzzle ) -> int:
    assert( init_puzzle.n_dims == goal_puzzle.n_dims , "Puzzles must have equal dimensions" )
    count_misplaced = 0
    for i in range( init_puzzle.n_dims ):
        for j in range( init_puzzle.n_dims ):
            if init_puzzle.board[i][j] != goal_puzzle.board[i][j]:
                count_misplaced += 1
    return count_misplaced

def is_goal( curr_puzzle: Puzzle , goal_puzzle: Puzzle ) -> int:
    assert( curr_puzzle.n_dims == goal_puzzle.n_dims , "Puzzles must have equal dimensions" )
    for i in range( curr_puzzle.n_dims ):
        for j in range( curr_puzzle.n_dims ):
            if curr_puzzle.board[i][j] != goal_puzzle.board[i][j]:
                return False
    return True

init_puzzle = Puzzle( [ [ 1 , 2 , 3 ] , [ 0 , 4 , 6 ] , [ 7 , 5 , 8 ] ] )
print( "Initial state:" )
init_puzzle.print()

goal_puzzle = Puzzle( [ [ 1 , 2 , 3 ] , [ 4 , 5 , 6 ] , [ 7 , 8 , 0 ] ] )
print( "Goal state:" )
goal_puzzle.print()

open_set: list[Puzzle] = [ init_puzzle ]

g_score: dict[Puzzle,int] = {}
g_score[ init_puzzle ] = 0

f_score: dict[Puzzle,int] = {}
g_score[ init_puzzle ] = heuristic(init_puzzle, goal_puzzle)

print( "Steps: ")
while len( open_set ) != 0:

    min_f_score_node = open_set[0]
    min_f_score = f_score.get( min_f_score_node , INFINITY )
    for node in open_set:
        score = f_score.get( node , INFINITY )
        if score < min_f_score:
            min_f_score = score 
            min_f_score_node = node
    
    current = min_f_score_node
    print( "-----------------------------" )
    current.print()
    if is_goal( current, goal_puzzle ):
        print( "Done" ) 
        break

    open_set.remove( current )
    for neighbor in move( current ):
        tent_g_score = g_score.get( current , INFINITY ) + 1
        if tent_g_score < g_score.get( neighbor , INFINITY ):
            g_score[ neighbor ] = tent_g_score
            f_score[ neighbor ] = tent_g_score + heuristic( neighbor , goal_puzzle )
            if neighbor not in open_set:
                open_set.append( neighbor )
 
