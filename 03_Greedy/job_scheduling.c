#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t id ; 
	size_t deadline ; 
	size_t profit ; 
} Job ; 

size_t greedy_scheduling(
	Job* jobs , 
	size_t n
) {
    // Sort the jobs in the decreasing order of their profit
	for( int i = 0 ; i < n ; i++ ) {
		int j = i ; 
		while( jobs[j].profit > jobs[j-1].profit && j > 0 ) {	
			Job temp = jobs[j-1] ; 
			jobs[j-1] = jobs[j] ; 
			jobs[j] = temp ;
			j-- ; 
		}
	}

    // Calculate max. permissible time to
    // complete the jobs
	size_t max_deadline = 0;
	for( size_t i = 0 ; i < n ; i++ ) {
		if( jobs[i].deadline > max_deadline ) {
			max_deadline = jobs[i].deadline ; 
		}
	}

    // Select jobs from the sorted jobs array
    // respecting the max_deadline
	size_t remaining_time = max_deadline ; 
	size_t profit = 0 ; 
	for( size_t i = 0 ; i < n ; i++ ) {
		if( jobs[i].deadline <= remaining_time ) {
			remaining_time -= jobs[i].deadline ;
			profit += jobs[i].profit ;  
		}
	} 
	
    return profit ; 
}

int main( int argc , char** argv ) {
	Job jobs[] = {
		{ 1 , 2 , 20 } , 
		{ 2 , 2 , 60 } , 
		{ 3 , 1 , 40 } , 
		{ 4 , 3 , 100 } , 
		{ 5 , 4 , 80 }
	} ; 
    size_t max_profit = greedy_scheduling( jobs , 5 ) ;
    printf( "Maximum profit is %li" , max_profit  ) ;  
	return 0;
}
