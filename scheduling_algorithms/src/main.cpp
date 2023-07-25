#include "first_come_first_serve.cpp"
#include "priority.cpp"
#include "metrics.cpp"

int main() {

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

    FirstComeFirstServe firstComeFirstServe( processes ); 
    std::vector<Process> output = firstComeFirstServe.schedule() ; 
    for( Process p : output ) {
        std::cout << p << "\n" ; 
    }
    std::cout << "Avg TAT: " << Metrics::getAverageTAT( output ) << "\n" ; 
    std::cout << "Avg WT: " << Metrics::getAverageWT( output ) << "\n" ; 


    // Priority First
    int priorities[5] = { 1 , 4 , 5 , 2 , 3 } ; 
    std::vector<Process> processes2;
    for( int i = 0 ; i < 5 ; i++ ) {
        Process p; 
        p.name = "P" + std::to_string(i+1);
        p.burstTime = burstTimes[i];
        p.arrivalTime = arrivalTimes[i];
        p.priority = priorities[i];
        processes2.push_back( p ) ; 
    }

    Priority priority( processes2 ); 
    std::vector<Process> output2 = priority.schedule() ; 
    for( Process p : output2 ) {
        std::cout << p << "\n" ; 
    }
    std::cout << "Avg TAT: " << Metrics::getAverageTAT( output2 ) << "\n" ; 
    std::cout << "Avg WT: " << Metrics::getAverageWT( output2 ) << "\n" ; 


    return 0;
}