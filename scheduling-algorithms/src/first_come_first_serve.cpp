#include "process.hpp"
#include <vector>
#include <queue>

class FirstComeFirstServe {

    std::vector<Process> processes;

    public:

    FirstComeFirstServe( std::vector<Process> processes ) {
        this -> processes = processes;
    }

    void schedule() {

        std::queue<Process> readyQueue; 
        std::vector<Process> output;    // Stores completed processes

        long time = 0 ;
        bool isExecuting = false ;      // A flag to check if a process is executing currently
        Process currentProcess = processes[0];  // Stores the currently executing process
        int n = 0;      // Indicates number of completed processes. Equals the size of `output`

        // Loop till n < processes.size()
        // and increment time at each iteration
        while( n < processes.size() ) {

            // Add processes to ready queue if any arrives
            // To check if a process has arrived, match
            // `time` with each process's arrivalTime
            for( Process p : processes ) {
                if( p.arrivalTime == time ) {
                    readyQueue.push( p ) ; 
                }
            }

            // If the CPU is in the executing state (i.e. isExecuting=true)
            // and time = currentProcess's completion time, then store currentProcess
            // in `output` after calculating the required parameters
            // For FCFS, CT = RT + BT
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
            // schedule a process from the readyQueue by popping it
            if( !readyQueue.empty() && !isExecuting ) {
                currentProcess = readyQueue.front() ; 
                readyQueue.pop() ; 
                // Response time indicates the time 
                // when the process received CPU for the 
                // first time
                currentProcess.responseTime = time ; 
                isExecuting = true ;  // Set isExecuting=true to indicate that currentProcess has
                                      // started execution
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