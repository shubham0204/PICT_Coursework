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
        std::vector<Process> output;
        long time = 0 ; 
        bool isExecuting = false ; 
        Process currentProcess = processes[0]; 
        int n = 0; 
        while( n < processes.size() ) {

            // Add processes to ready queue if any arrives
            for( Process p : processes ) {
                if( p.arrivalTime == time ) {
                    readyQueue.push( p ) ; 
                }
            }
            

            if( !isExecuting ) {
                currentProcess = readyQueue.front() ; 
                currentProcess.responseTime = time ; 
                readyQueue.pop() ; 
                isExecuting = true ; 
            }

            if( isExecuting && time == currentProcess.responseTime + currentProcess.burstTime ) {
                isExecuting = false ; 
                currentProcess.completionTime = time ; 
                currentProcess.turnAroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitTime = currentProcess.turnAroundTime - currentProcess.burstTime;
                output.push_back( currentProcess ) ; 
                n++ ; 
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