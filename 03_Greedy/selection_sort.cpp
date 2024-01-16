#include <iostream>
#include <vector>

void selection_sort(
    std::vector<int>& input
) {
    for( size_t i = 0 ; i < input.size() ; i++ ) {
        // At position `i`, the best element that can placed
        // is the `i`th smallest element in the array
        // See: https://www2.seas.gwu.edu/~ayoussef/cs6212/greedy.html
        int min_element = input[ i ] ; 
        size_t min_element_index = i ; 
        for( size_t j = i + 1 ; j < input.size() ; j++ ) {
            if( input[j] < min_element ) {
                min_element = input[j] ; 
                min_element_index = j ; 
            }
        }
        std::swap( input[i] , input[ min_element_index ] ) ; 
    }
}

void print_array(
    std::vector<int>& input
) {
    for( const int& num: input ) {
        std::cout << num << " " ; 
    }
    std::cout << '\n' ;
}

int main( int argc , char* argv[] ) {
    std::vector<int> nums = { 2 , 3 , 1 , 7 , 5 , 2 , 3 , 0 } ; 
    selection_sort( nums ) ; 
    print_array( nums ) ; 
    return 0;
}