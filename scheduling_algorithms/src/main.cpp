#include "first_come_first_serve.cpp"
#include "shortest_job_first.cpp"
#include "round_robin.cpp"
#include "priority.cpp"

void algorithm_1() {
    // Problem source: 
    // https://www.geeksforgeeks.org/first-come-first-serve-cpu-scheduling-non-preemptive/
    long burstTimes[5] = { 3 , 6 , 1 , 2 , 4 } ; 
    long arrivalTimes[5] = { 0 , 1 , 3 , 2 , 4 } ; 
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
    // Problem source:
    // https://www.geeksforgeeks.org/shortest-remaining-time-first-preemptive-sjf-scheduling-algorithm/
    long burstTimes[5] = { 3 , 6 , 1 , 2 , 4 } ; 
    long arrivalTimes[5] = { 0 , 1 , 3 , 2 , 4 } ; 
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
    // Problem source:
    // https://www.geeksforgeeks.org/round-robin-scheduling-with-different-arrival-times/
    long burstTimes[5] = { 3 , 6 , 1 , 2 , 4 } ; 
    long arrivalTimes[5] = { 0 , 1 , 3 , 2 , 4 } ; 
    std::vector<Process> processes;
    for( int i = 0 ; i < 5 ; i++ ) {
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
    // Problem source:
    // https://www.geeksforgeeks.org/priority-cpu-scheduling-with-different-arrival-time-set-2/
    long burstTimes[5] = { 3 , 6 , 1 , 2 , 4 } ; 
    long arrivalTimes[5] = { 0 , 1 , 3 , 2 , 4 } ; 
    int priorities[5] = { 3 , 4 , 9 , 7 , 8 } ; 
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

    /*
    algorithm_1();
    algorithm_2();
    algorithm_3();
    algorithm_4();
    */

    std::vector<Process> inputProcesses;
    std::cout << "Enter no. of processes: " << "\n" ;
    int n = 0; std::cin >> n ; 
    for( int i = 0 ; i < n ; i++ ) {
        int at, bt ; 
        int priority = 0;
        std::cout << "Enter <AT> <BT> <priority> for process p" << (i+1) << "\n" ; 
        std::cin >> at >> bt >> priority;
        Process p;
        p.name = "P" + std::to_string(i+1);
        p.arrivalTime = at ; 
        p.burstTime = bt ; 
        p.priority = priority ; 
        inputProcesses.push_back( p ) ; 
    }

    while( true ) {
        std::cout << "1. FCFS" << "\n" ; 
        std::cout << "2. Priority-based" << "\n" ; 
        std::cout << "3. SJF" << "\n" ; 
        std::cout << "4. Round Robin" << "\n" ; 
        int option = -1 ; std::cin >> option;

        if( option == 1 ) {
            FirstComeFirstServe algo( inputProcesses ) ; 
            algo.schedule() ;
        }
        else if( option == 2 ) {
            Priority algo( inputProcesses ) ; 
            algo.schedule() ;
        }
        else if( option == 3 ) {
            ShortestJobFirst algo( inputProcesses ) ; 
            algo.schedule() ;
        }
        else if( option == 4 ) {
            RoundRobin algo( inputProcesses ) ; 
            std::cout << "Enter time quantum for Round Robin: " << "\n" ; 
            long quantum = 2L ; std::cin >> quantum ; 
            algo.schedule( quantum ) ;
        }
        else {
            break;
        }
    }
    return 0;
}

