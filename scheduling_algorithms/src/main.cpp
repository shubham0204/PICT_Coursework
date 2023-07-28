#include "first_come_first_serve.cpp"
#include "shortest_job_first.cpp"
#include "round_robin.cpp"
#include "priority.cpp"

void algorithm_1() {
    long burstTimes[5] = { 6 , 2 , 8 , 3 , 4 } ; 
    long arrivalTimes[5] = { 2 , 5 , 1 , 0 , 4 } ; 
    std::vector<Process> processes;
    for( int i = 0 ; i < 5 ; i++ ) {
        Process p; 
        p.name = "P" + std::to_string(i+1);
        p.burstTime = burstTimes[i];
        p.arrivalTime = arrivalTimes[i];
        processes.push_back( p ) ; 
    }
    std::cout << "First-Come-First-Serve scheduling: " << "\n" ;
    FirstComeFirstServe firstComeFirstServe( processes ); 
    firstComeFirstServe.schedule() ; 
}


void algorithm_2() {
    long burstTimes[5] = { 6 , 2 , 8 , 3 , 4 } ; 
    long arrivalTimes[5] = { 2 , 5 , 1 , 0 , 4 } ; 
    std::vector<Process> processes;
    for( int i = 0 ; i < 5 ; i++ ) {
        Process p; 
        p.name = "P" + std::to_string(i+1);
        p.burstTime = burstTimes[i];
        p.arrivalTime = arrivalTimes[i];
        processes.push_back( p ) ; 
    }
    std::cout << "Shortest Job First scheduling: " << "\n" ;
    ShortestJobFirst shortestJobFirst( processes ) ; 
    shortestJobFirst.schedule() ;
}

void algorithm_3() {
    long burstTimes[4] = { 5 , 4 , 2 , 1 } ; 
    long arrivalTimes[4] = { 0 , 1 , 2 , 3 } ; 
    std::vector<Process> processes;
    for( int i = 0 ; i < 4 ; i++ ) {
        Process p; 
        p.name = "P" + std::to_string(i+1);
        p.burstTime = burstTimes[i];
        p.arrivalTime = arrivalTimes[i];
        processes.push_back( p ) ; 
    }
    std::cout << "Round-Robin scheduling: " << "\n" ;
    RoundRobin roundRobin( processes ) ;
    roundRobin.schedule( 2L ) ; 
}

void algorithm_4() {
    long burstTimes[5] = { 6 , 2 , 8 , 3 , 4 } ; 
    long arrivalTimes[5] = { 2 , 5 , 1 , 0 , 4 } ; 
    int priorities[5] = { 1 , 4 , 5 , 2 , 3 } ; 
    std::vector<Process> processes;
    for( int i = 0 ; i < 5 ; i++ ) {
        Process p; 
        p.name = "P" + std::to_string(i+1);
        p.burstTime = burstTimes[i];
        p.arrivalTime = arrivalTimes[i];
        p.priority = priorities[i];
        processes.push_back( p ) ; 
    }
    std::cout << "Priority-based scheduling: " << "\n" ;
    Priority priority( processes ); 
    priority.schedule() ; 
}

int main() {

    algorithm_1() ; 
    algorithm_2() ; 
    algorithm_3() ; 
    algorithm_4() ; 

    return 0;
}

