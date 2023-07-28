#include "process.hpp"
#include <vector>
#include <queue>
#include <algorithm>
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

            if( currentProcessRemainingBT == 0L ) {
                currentProcess.burstTime = burstTimes[currentProcess.name];
                currentProcess.completionTime = time ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++ ;
                isExecuting = false ; 

                if( !readyQueue.empty() ) {

                    std::sort( readyQueue.begin() , readyQueue.end() , []( const Process& p1 , const Process& p2 ){
                        return p1.burstTime < p2.burstTime ;
                    });
                    if( readyQueue[0].responseTime == 0L ) readyQueue[0].responseTime = time;
                    currentProcessRemainingBT = readyQueue[0].burstTime ; 
                    currentProcess = readyQueue[0];
                    readyQueue.erase( readyQueue.begin() ) ; 
                    isExecuting = true;
                }
            }
            else {
                if( !readyQueue.empty() ) {
                    std::sort( readyQueue.begin() , readyQueue.end() , []( const Process& p1 , const Process& p2 ){
                        return p1.burstTime < p2.burstTime ;
                    });
                    if( isExecuting ) {
                        if( readyQueue[0].burstTime < currentProcessRemainingBT ) {
                            currentProcess.burstTime = currentProcessRemainingBT ; 
                            readyQueue.push_back( currentProcess ) ; 
                            currentProcess = readyQueue[ 0 ] ; 
                            readyQueue.erase( readyQueue.begin() ) ; 
                            currentProcessRemainingBT = currentProcess.burstTime ; 
                            isExecuting = true;
                        } 
                    }
                    else {
                        currentProcess = readyQueue[ 0 ] ; 
                        readyQueue.erase( readyQueue.begin() ) ; 
                        currentProcessRemainingBT = currentProcess.burstTime ; 
                        isExecuting = true;
                    }
                
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