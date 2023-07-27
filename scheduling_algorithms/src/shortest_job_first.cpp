#include "process.hpp"
#include <vector>
#include <queue>
#include <unordered_map>

class ShortestJobFirst {

    std::vector<Process> processes;

    public:

    ShortestJobFirst( std::vector<Process> processes ) {
        this -> processes = processes;
    }

    void schedule() {

        std::unordered_map<std::string,long> burstTimes;
        for( Process p : processes ) {
            burstTimes[ p.name ] = p.burstTime ; 
        }

        std::vector<Process> readyQueue;
        std::vector<Process> output;
        long time = 0 ; 
        bool isExecuting = false ; 

        Process currentProcess = processes[0]; 
        long currentProcessRemainingBT = 10000L ;

        int n = 0; 
        while( n < processes.size() ) {

            // Add processes to ready queue if any arrives
            for( Process p : processes ) {
                if( p.arrivalTime == time ) {
                    readyQueue.push_back( p ) ; 
                }
            }

            // Find minimum burst time process from ready queue
            long minBurstTime = 100000L ;
            int processIndex = -1 ;
            for( int i = 0 ; i < readyQueue.size() ; i++ ) {
                if( readyQueue[i].burstTime < minBurstTime ) {
                    minBurstTime = readyQueue[i].burstTime;
                    processIndex = i;
                }
            }

            if( minBurstTime < currentProcessRemainingBT ) {
                if( isExecuting ) {
                    currentProcess.burstTime = currentProcessRemainingBT ; 
                    readyQueue.push_back( currentProcess ) ; 
                }
                currentProcess = readyQueue[ processIndex ] ; 
                if( currentProcess.responseTime == 0L ) currentProcess.responseTime = time ; 
                readyQueue.erase( readyQueue.begin() + processIndex );
                isExecuting = true ; 
                currentProcessRemainingBT = currentProcess.burstTime;
            }

            if( !isExecuting ) {
                currentProcess = readyQueue[ processIndex ] ; 
                if( currentProcess.responseTime == 0L ) currentProcess.responseTime = time ; 
                readyQueue.erase( readyQueue.begin() + processIndex );
                isExecuting = true ; 
                currentProcessRemainingBT = currentProcess.burstTime;
            }

            if( currentProcessRemainingBT == 0L ) {
                isExecuting = false ; 
                currentProcess.burstTime = burstTimes[currentProcess.name];
                currentProcess.completionTime = time ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++ ; 
            }

            if( isExecuting ) {
                currentProcessRemainingBT-- ; 
            }

            time++ ; 
        }
        float avgTAT = 0.0f ; 
        float avgWT = 0.0f;
        for( Process p : output ) {
            avgTAT += p.turnAroundTime ; 
            avgWT += p.waitTime;
            std::cout << p << "\n" ; 
        }
        avgTAT /= output.size() ; 
        avgWT /= output.size() ; 

        std::cout << "Average TAT: " << avgTAT << "\n" ; 
        std::cout << "Average WT: " << avgWT << "\n" ;  
    }

} ;