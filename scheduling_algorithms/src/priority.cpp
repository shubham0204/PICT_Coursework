#include "process.hpp"
#include <vector>
#include <queue>

class Priority {

    std::vector<Process> processes;

    public:

    Priority( std::vector<Process> processes ) {
        this -> processes = processes;
    }

    void schedule() {
        std::vector<Process> readyQueue;  // We use vector as a queue here
        std::vector<Process> output;    // Stores completed processes

        long time = 0 ;
        bool isExecuting = false ;      // A flag to check if a process is executing currently
        Process currentProcess = processes[0];  // Stores the currently executing process
        int n = 0;      // Indicates number of completed processes. Equals the size of `output`

        // Loop till n < processes.size()
        // and increment time at each iteration
        while( n < processes.size() ) {

            // Add processes to readyQueue if any arrives
            // To check if a process has arrived, match
            // `time` with each process's arrivalTime
            for( Process p : processes ) {
                if( p.arrivalTime == time ) {
                    readyQueue.push_back( p ) ; 
                }
            }

            // If the CPU is in the executing state (i.e. isExecuting=true)
            // and time = currentProcess's completion time, then store currentProcess
            // in `output` after calculating the required parameters
            // For FCFS and Priority scheduling, CT = RT + BT
            if( isExecuting && time == currentProcess.responseTime + currentProcess.burstTime ) {
                isExecuting = false ; 
                currentProcess.responseTime -= currentProcess.arrivalTime;
                currentProcess.completionTime = time ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++ ; 
            }
            
            // If no process is executing currently
            // schedule a process from the readyQueue by
            // fetching the process with the highest priority (numerically least priority)
            if( !readyQueue.empty() && !isExecuting ) {
                int maxPriority = 1000;
                int processIndex = 0 ;
                for( int i = 0 ; i < readyQueue.size() ; i++ ) {
                    if( readyQueue[i].priority < maxPriority ) {
                        maxPriority = readyQueue[i].priority;
                        currentProcess = readyQueue[i];
                        processIndex = i;
                    }
                }
                currentProcess.responseTime = time ; 
                // Delete the process from the readyQueue
                readyQueue.erase( readyQueue.begin() + processIndex );
                isExecuting = true ; 
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