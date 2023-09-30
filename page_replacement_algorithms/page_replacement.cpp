#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
using std::vector, std::deque, std::cout, std::cin, std::find ;

class PageReplacement {

    vector<uint16_t> pageNumbers ; 
    uint16_t maxNumFrames ;

    public:

    PageReplacement( 
        const vector<uint16_t>& pageNumbers , 
        const uint16_t& maxNumFrames
        ) {
        this -> pageNumbers = pageNumbers ;
        this -> maxNumFrames = maxNumFrames ; 
    }
    
    float firstInFirstOut() {
        deque<uint16_t> q; 
        uint16_t pageFaultCount = 0;
        for( uint16_t i = 0 ; i < pageNumbers.size() ; i++ ) {
            if( find( q.begin() , q.end() , pageNumbers[i] ) == q.end() ) {
                // Page fault occurred
                pageFaultCount++ ; 
                cout << "Miss" << '\n' ; 
                if( q.size() == maxNumFrames ) { q.pop_front() ; }
                q.push_back( pageNumbers[i] ) ; 
            }
            else {
                cout << "Hit" << '\n' ; 
            }
        }
        return ((float) pageFaultCount) / (float)pageNumbers.size() ; 
    }

    float leastRecentlyUsed() {
        vector<uint16_t> v; 
        vector<uint16_t> ages;
        uint16_t pageFaultCount = 0;

        for( uint16_t i = 0 ; i < pageNumbers.size() ; i++ ) {

            std::for_each( ages.begin() , ages.end() , []( uint16_t& element ) {
                element++ ; 
            } ) ; 

            if( find( v.begin() , v.end() , pageNumbers[i] ) == v.end() ) {
                // Page fault occurred
                pageFaultCount++ ; 
                cout << "Miss" << "\n" ;
                if( v.size() == maxNumFrames ) {
                    int maxElementIndex = std::max_element( ages.begin() , ages.end() ) - ages.begin() ; 
                    ages.erase( ages.begin() + maxElementIndex ) ; 
                    v.erase( v.begin() + maxElementIndex ) ; 
                    v.insert( v.begin() + maxElementIndex , pageNumbers[i] ) ; 
                    ages.insert( ages.begin() + maxElementIndex , 0 ) ; 
                }
                else {
                    v.insert( v.begin() , pageNumbers[i] ) ; 
                    ages.insert( ages.begin() , 0 ) ;
                }
            }
            else {
                cout << "Hit" << "\n" ;
            }
        }
        return ((float) pageFaultCount) / pageNumbers.size() ; 
    }

    



} ; 

int main( int arg , char* argv[] ) {

    vector<uint16_t> frameNumbers = { 3, 1, 2, 1, 6, 5, 1, 3 } ; 
    PageReplacement algo( frameNumbers , 3 ) ; 
    float fifoRatio = algo.firstInFirstOut() ; 
    cout << fifoRatio << '\n' ; 
    float lruRatio = algo.leastRecentlyUsed() ; 
    cout << lruRatio << '\n' ;  

    return 0;
}