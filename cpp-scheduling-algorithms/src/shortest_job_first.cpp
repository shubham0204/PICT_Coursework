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

        // For preemptive scheduling algorithms, the burstTime of `processes`
        // will be modified in further steps,
        // hence we store the user-given burstTimes in a hashmap
        // for later use
        std::unordered_map<std::string,long> burstTimes;
        for( Process p : processes ) {
            burstTimes[ p.name ] = p.burstTime ; 
        }

        std::vector<Process> readyQueue; // Use vector as a queue here
        std::vector<Process> output;    // Stores completed processes

        long time = 0 ;
        bool isExecuting = false ;      // A flag to check if a process is executing currently
        Process currentProcess = processes[0];  // Stores the currently executing process
        int n = 0;      // Indicates number of completed processes. Equals the size of `output`
        int step = 0 ;    // Indicates the time when the currentProcess should be preempted
                          // and a new process should be scheduled
        long currentProcessRemainingBT = 1000L;     // The burstTime (execution time) remaining
        // for currentProcess. It is decremented by 1 at each time-step.

        while( n < processes.size() ) {

            // Add processes to ready queue if any arrives
            // To check if a process has arrived, match
            // `time` with each process's arrivalTime
            for( Process p : processes ) {
                if( p.arrivalTime == time ) {
                    readyQueue.push_back( p ) ; 
                }
            }

            // `currentProcessRemainingBT` becomes 0 when the `currentProcess`
            // has finished its execution. In this case, we append `currentProcess` to
            // `output` after calculating the required parameters
            if( currentProcessRemainingBT == 0L ) {

                // Insert `currentProcess` in `output`
                // and set isExecuting=false as the CPU becomes idle
                currentProcess.responseTime -= currentProcess.arrivalTime;
                currentProcess.burstTime = burstTimes[currentProcess.name];
                currentProcess.completionTime = time ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++ ;
                isExecuting = false ; 

                // If there exists a process in the readyQueue,
                // schedule it for execution as the CPU is idle
                if( !readyQueue.empty() ) {
                    // Sort processes in the readyQueue according to
                    // their burstTimes in increasing order.
                    std::sort( readyQueue.begin() , readyQueue.end() , []( const Process& p1 , const Process& p2 ){
                        return p1.burstTime < p2.burstTime ;
                    });
                    // The first process in the readyQueue will have the least burstTime
                    // Set it as the currentProcess and change `isExecuting` to true
                    if( readyQueue[0].responseTime == 0L ) readyQueue[0].responseTime = time;
                    currentProcessRemainingBT = readyQueue[0].burstTime ; 
                    currentProcess = readyQueue[0];
                    readyQueue.erase( readyQueue.begin() ) ; 
                    isExecuting = true;
                }
            }
            else {
                if( !readyQueue.empty() ) {
                    // If the readyQueue is not empty,
                    // sort processes in the readyQueue according to their burstTimes
                    std::sort( readyQueue.begin() , readyQueue.end() , []( const Process& p1 , const Process& p2 ){
                        return p1.burstTime < p2.burstTime ;
                    });
                    if( isExecuting ) {
                        // readyQueue[0] is the process with least burstTime in the readyQueue
                        // If the burstTime of that process is smaller
                        // than the remaining burstTime of the currently executing process,
                        // then preempt the currentProcess
                        // and start execution of readyQueue[0]
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
                        // If no process was executing (hence no process to preempt)
                        // schedule process readyQueue[0]
                        currentProcess = readyQueue[ 0 ] ; 
                        readyQueue.erase( readyQueue.begin() ) ; 
                        currentProcessRemainingBT = currentProcess.burstTime ; 
                        isExecuting = true;
                    }
                
                }
            }

            // Decrement currentProcessRemainingBT only if a process
            // is executing currently
            if( isExecuting ) {
                currentProcessRemainingBT-- ; 
            }

            time++ ; 
        }

        // Compute average turnAroundTime and waitTime
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