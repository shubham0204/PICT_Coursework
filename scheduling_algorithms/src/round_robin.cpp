#include "process.hpp"
#include <vector>
#include <queue>
#include <unordered_map>

class RoundRobin {

    std::vector<Process> processes;

    public:

    RoundRobin( std::vector<Process> processes ) {
        this -> processes = processes;
    }

    void schedule( long quantum ) {

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
        int step = 0 ; 
        while( n < processes.size() ) {

            // Add processes to ready queue if any arrives
            for( Process p : processes ) {
                if( p.arrivalTime == time ) {
                    readyQueue.push_back( p ) ; 
                }
            }

            if( currentProcessRemainingBT == 0L ) {
                currentProcess.completionTime = time ; 
                currentProcess.burstTime = burstTimes[ currentProcess.name ] ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++;

                isExecuting = false ; 
                if( !readyQueue.empty() ) {
                    currentProcess = readyQueue[0] ; 
                    if( currentProcess.responseTime == 0L ) currentProcess.responseTime = time;
                    currentProcessRemainingBT = currentProcess.burstTime ; 
                    step = step + quantum ; 
                    isExecuting = true;
                    readyQueue.erase( readyQueue.begin() ) ;
                }
            }

            if( isExecuting ) {
                if( time == step ) {
                    currentProcess.burstTime = currentProcessRemainingBT ; 
                    readyQueue.push_back( currentProcess ) ; 

                    if( !readyQueue.empty() ) {
                        currentProcess = readyQueue[0] ; 
                        if( currentProcess.responseTime == 0L ) currentProcess.responseTime = time;
                        currentProcessRemainingBT = currentProcess.burstTime ; 
                        step = step + quantum ; 
                        isExecuting = true;
                        readyQueue.erase( readyQueue.begin() ) ;
                    }
                }
            }
            else {
                if( !readyQueue.empty() ) {
                        currentProcess = readyQueue[0] ; 
                        currentProcessRemainingBT = currentProcess.burstTime ; 
                        step = step + quantum ; 
                        isExecuting = true;
                        readyQueue.erase( readyQueue.begin() ) ;
                    }
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