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
        // `quantum` is the time-interval when processes should be preempted
        // if their execution is not complete.

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

        // Loop till n < processes.size()
        // and increment time at each iteration
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
                currentProcess.completionTime = time ; 
                currentProcess.burstTime = burstTimes[ currentProcess.name ] ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++;
                isExecuting = false ; 

                // If there exists a process in the readyQueue,
                // schedule it for execution as the CPU is idle
                if( !readyQueue.empty() ) {
                    currentProcess = readyQueue[0] ; 
                    // If the responseTime = 0L, meaning, the process was never preempted before,
                    // set its responseTime to `time`
                    if( currentProcess.responseTime == 0L ) currentProcess.responseTime = time;
                    currentProcessRemainingBT = currentProcess.burstTime ; 
                    step = step + quantum ; 
                    isExecuting = true;
                    readyQueue.erase( readyQueue.begin() ) ;
                }
            }

            // If a process is currently executing, and `time`
            // equals `step`, then we need to preempt the current process
            if( isExecuting ) {
                if( time == step ) {
                    // Update currentProcess's burstTime and push it 
                    // to the readyQueue
                    currentProcess.burstTime = currentProcessRemainingBT ; 
                    readyQueue.push_back( currentProcess ) ; 

                    // If readyQueue is not empty, schedule a new process
                    // from the readyQueue. Increment `step` with the given
                    // time quantum.
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
                // If no process is executing currently,
                // and the readyQueue is not empty,
                // schedule a process from the readyQueue
                if( !readyQueue.empty() ) {
                        currentProcess = readyQueue[0] ; 
                        currentProcessRemainingBT = currentProcess.burstTime ; 
                        step = step + quantum ; 
                        isExecuting = true;
                        readyQueue.erase( readyQueue.begin() ) ;
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