#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
using std::vector, std::deque, std::cout, std::cin, std::find ;

class PageReplacement {

    vector<int> pageNumbers ; 
    int maxNumFrames ;

    public:

    PageReplacement( 
        const vector<int>& pageNumbers , 
        const int& maxNumFrames
        ) {
        this -> pageNumbers = pageNumbers ;
        this -> maxNumFrames = maxNumFrames ; 
    }
    
    float firstInFirstOut() {
        deque<int> q; 
        int pageFaultCount = 0;
        for( int i = 0 ; i < pageNumbers.size() ; i++ ) {
            for( int page : q ) { cout << page << " " ; }
            cout << "\n" ; 
            if( find( q.begin() , q.end() , pageNumbers[i] ) == q.end() ) {
                // Page fault occurred
                pageFaultCount++ ; 
                if( q.size() == maxNumFrames ) { q.pop_front() ; }
                q.push_back( pageNumbers[i] ) ; 
            }
        }
        return ((float) pageFaultCount) / (float)pageNumbers.size() ; 
    }

    float leastRecentlyUsed() {
        vector<int> v; 
        vector<int> ages;
        int pageFaultCount = 0;

        for( int i = 0 ; i < pageNumbers.size() ; i++ ) {
            for( int page : v ) { cout << page << " " ; }
            cout << "\n" ; 

            std::for_each( ages.begin() , ages.end() , []( int& element ) {
                element++ ; 
            } ) ; 

            if( find( v.begin() , v.end() , pageNumbers[i] ) == v.end() ) {
                // Page fault occurred
                pageFaultCount++ ; 
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
                // Reset age of currently accessed page 
                int index = find( v.begin() , v.end() , pageNumbers[i] ) - v.begin() ;
                ages[ index ] = 0 ; 
            }
        }
        return ((float) pageFaultCount) / pageNumbers.size() ; 
    }

    float optimal() {
        vector<int> v; 
        int pageFaultCount = 0;
        for( int i = 0 ; i < pageNumbers.size() ; i++ ) {
            for( int page : v ) { cout << page << " " ; }
            cout << "\n" ; 
            if( find( v.begin() , v.end() , pageNumbers[i] ) == v.end() ) {
                // Page fault occurred
                pageFaultCount++ ; 
                if( v.size() == maxNumFrames ) {
                    int maxUsageGap = -1 ; 
                    int maxUsageGapIndex = 0 ;
                    for( int p = 0 ; p < maxNumFrames ; p++ ) {
                        bool isFound = false ; 
                        for( int j = i + 1 ; j < pageNumbers.size() ; j++ ) {
                            if( pageNumbers[j] == v[p] ) {
                                isFound = true;
                                if( (j-i) > maxUsageGap ) {
                                    maxUsageGap = j - i ; 
                                    maxUsageGapIndex = p ; 
                                }
                            }
                        }
                        if( !isFound ) {
                            maxUsageGapIndex = p ; 
                            break;
                        }
                    }
                    v[ maxUsageGapIndex ] = pageNumbers[i] ; 
                }
                else {
                    v.push_back( pageNumbers[i] ) ; 
                }
            }
        }
        return ((float) pageFaultCount) / (float)pageNumbers.size() ; 
    }

} ; 

int main( int arg , char* argv[] ) {

    vector<int> frameNumbers = { 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 } ; 
    PageReplacement algo( frameNumbers , 3 ) ; 

    cout << "First In First Out (FIFO): " << '\n' ; 
    float fifoRatio = algo.firstInFirstOut() ; 
    cout << "Miss Ratio: " << fifoRatio << '\n' ; 

    cout << "Least Recently Used (LRU): " << '\n' ; 
    float lruRatio = algo.leastRecentlyUsed() ; 
    cout << "Miss Ratio: " << lruRatio << '\n' ;  

    cout << "Optimal: " << '\n' ; 
    float optimalRatio = algo.optimal() ; 
    cout << "Miss Ratio: " << optimalRatio << '\n' ; 

    return 0;
}