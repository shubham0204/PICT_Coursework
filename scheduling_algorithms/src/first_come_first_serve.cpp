#include "process.hpp"
#include <vector>
#include <queue>

class FirstComeFirstServe {

    std::vector<Process> processes;

    public:

    FirstComeFirstServe( std::vector<Process> processes ) {
        this -> processes = processes;
    }

    std::vector<Process> schedule() {
        for( int i = 0 ; i < processes.size() ; i++ ) {
            for( int j = i ; j > 0 ; j-- ) {
                if( processes[j].arrivalTime < processes[j-1].arrivalTime ) {
                    Process temp = processes[j] ; 
                    processes[j] = processes[j-1] ; 
                    processes[j-1] = temp;
                } 
            }
        }

        std::queue<Process> readyQueue;
      
        for( Process p : processes ) {
            readyQueue.push( p ) ; 
        }

        int time = 0; 
        std::vector<Process> scheduledProcesses;
        while( !readyQueue.empty() ) {
            Process p = readyQueue.front() ; 
            readyQueue.pop() ; 
            p.completionTime = time + p.burstTime ;
            p.turnAroundTime = p.completionTime - p.arrivalTime;
            p.waitTime = p.turnAroundTime - p.burstTime;
            p.responseTime = p.waitTime;
            scheduledProcesses.push_back( p ) ; 
            time += p.burstTime;
        }

        return scheduledProcesses;
    } 


} ; 