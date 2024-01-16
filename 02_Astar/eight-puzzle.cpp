#include <iostream>
#include <vector>

#define STAR '*'

class Puzzle {

    size_t dim ;
    size_t* board ; 

    public:

    Puzzle(
            size_t dim 
          ) {
        this -> dim = dim ;
        this -> board = new size_t[ this -> dim * this -> dim ] ;  
    }

    std::vector<std::pair<size_t,size_t>> get_possible_moves(
            const size_t x , 
            const size_t y
            ) {
        std::vector<std::pair<size_t,size_t>> possible_moves ; 
        if( ( x + 1 ) < dim && y < dim ) {
            possible_moves.push_back( { x + 1 , y } ) ; 
        }
        if( x < dim && ( y + 1 ) < dim ) {
            possible_moves.push_back( { x , y + 1 } ) ; 
        }
        if( ( x - 1 ) >= 0 && y >= 0 ) {
            possible_moves.push_back( { x - 1 , y } ) ; 
        }
        if( x >= 0 && ( y - 1 ) >= 0 ) {
            possible_moves.push_back( { x , y - 1 } ) ; 
        }
        return possible_moves ; 
    }

    void set_board_position(
            const size_t& x , 
            const size_t& y , 
            const uint8_t element 
            ) {
        board[ x * dim + y ] = element ;
    }

    void solve_a_star(
            const Puzzle& goal_state
            ) {
        
    }

    void print_board() {
        for( size_t i = 0 ; i < dim ; i++ ) {
            for( size_t j = 0 ; j < dim ; j++ ) {
                std::cout << board[ i * dim + j ] << ' ' ; 
            }
            std::cout << '\n' ; 
        }
    }

} ; 


int main( int argc , char* argv[] ) {
    Puzzle puzzle( 3 ) ;  
    for( size_t i = 0 ; i < 3 ; i++ ) {
        for( size_t j = 0 ; j < 3 ; j++ ) {
            puzzle.set_board_position(i, j, 10) ;  
        }
    }
    puzzle.print_board() ; 
    auto moves = puzzle.get_possible_moves( 1 , 1 ) ;
    for( const std::pair<size_t,size_t>& move : moves ) {
        std::cout << move.first << " " << move.second << '\n' ; 
    }
    return 0;
} 
