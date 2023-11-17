#include <vector>
#include <deque>
#include <algorithm>
#include <iostream>
using std::vector, std::deque, std::cout, std::cin, std::find ;

class PageReplacement {

    vector<int> pageReferences ; 
    int memorySize ;

    public:

    PageReplacement( 
        const vector<int>& pageReferences , 
        const int& maxNumFrames
        ) {
        this -> pageReferences = pageReferences ;
        this -> memorySize = maxNumFrames ; 
    }
    
    float firstInFirstOut() {
        deque<int> memory; 
        int pageFaultCount = 0;
        for( int i = 0 ; i < pageReferences.size() ; i++ ) {

            for( int page : memory ) { cout << page << " " ; }
            cout << "\n" ; 
            if( find( memory.begin() , memory.end() , pageReferences[i] ) == memory.end() ) {
                // Page fault occurred
                pageFaultCount++ ; 
                if( memory.size() == memorySize ) { memory.pop_front() ; }
                memory.push_back( pageReferences[i] ) ; 
            }
            
        }
        return ((float) pageFaultCount) / (float)pageReferences.size() ; 
    }

    float leastRecentlyUsed() {
        vector<int> memory; 
        vector<int> ages;
        int pageFaultCount = 0;

        for( int i = 0 ; i < pageReferences.size() ; i++ ) {
            for( int page : memory ) { cout << page << " " ; }
            cout << "\n" ; 

            std::for_each( ages.begin() , ages.end() , []( int& element ) {
                element++ ; 
            } ) ; 

            if( find( memory.begin() , memory.end() , pageReferences[i] ) == memory.end() ) {

                // Page fault occurred
                pageFaultCount++ ; 

                if( memory.size() == memorySize ) {

                    // maxAgeIndex refers to the index of the element 
                    // which was least recently accessed by the CPU
                    int maxAgeIndex = std::max_element( ages.begin() , ages.end() ) - ages.begin() ; 

                    // Reset age
                    ages.erase( ages.begin() + maxAgeIndex ) ; 
                    ages.insert( ages.begin() + maxAgeIndex , 0 ) ; 

                    // Swap in pageReferences[i] at position maxAgeIndex
                    memory.erase( memory.begin() + maxAgeIndex ) ; 
                    memory.insert( memory.begin() + maxAgeIndex , pageReferences[i] ) ; 
                }
                else {
                    memory.insert( memory.begin() , pageReferences[i] ) ; 
                    ages.insert( ages.begin() , 0 ) ;
                }

            }
            else {
                // Reset age of currently accessed page 
                int index = find( memory.begin() , memory.end() , pageReferences[i] ) - memory.begin() ;
                ages[ index ] = 0 ; 
            }
        }
        return ((float) pageFaultCount) / pageReferences.size() ; 
    }

    float optimal() {

        vector<int> memory; 
        int pageFaultCount = 0;

        for( int i = 0 ; i < pageReferences.size() ; i++ ) {

            // Display all pages
            for( int page : memory ) { cout << page << " " ; }
            cout << "\n" ; 

            // Check if page is in memory
            if( find( memory.begin() , memory.end() , pageReferences[i] ) == memory.end() ) {

                // Page is not in memory
                // Page fault occurred
                pageFaultCount++ ; 
                if( memory.size() == memorySize ) {
                    int maxUsageGap = -1 ; 
                    int maxUsageGapIndex = 0 ;

                    for( int frameIndex = 0 ; frameIndex < memorySize ; frameIndex++ ) {
                        bool isFound = false ; 
                        for( int refIndex = i + 1 ; refIndex < pageReferences.size() ; refIndex++ ) {
                            if( pageReferences[refIndex] == memory[frameIndex] ) {
                                isFound = true;
                                if( (refIndex-i) > maxUsageGap ) {
                                    maxUsageGap = refIndex - i ; 
                                    maxUsageGapIndex = frameIndex ; 
                                }
                            }
                        }
                        if( !isFound ) {
                            // If page at frameIndex i.e. memory[frameIndex] was never
                            // referred in the future, swap out this page
                            // and break loop, as we need search for any other candidates
                            maxUsageGapIndex = frameIndex ; 
                            break;
                        }
                    }
                    memory[ maxUsageGapIndex ] = pageReferences[i] ; 

                }
                else {

                    memory.push_back( pageReferences[i] ) ; 

                }
            }

        }
        return ((float) pageFaultCount) / (float)pageReferences.size() ; 
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