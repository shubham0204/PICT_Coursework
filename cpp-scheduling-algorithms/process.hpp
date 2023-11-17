#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>

class Process {

    public:

    std::string name;
    int priority = 0;
    long arrivalTime = 0L;
    long burstTime = 0L;
    long completionTime = 0L;
    long turnAroundTime = 0L;
    long waitTime = 0L;
    long responseTime = 0L;

    friend std::ostream& operator<<( std::ostream& outputStream , Process p ) {
        outputStream << p.name << " AT=" << p.arrivalTime << " Priority=" << p.priority << " BT=" << p.burstTime << 
        " CT=" << p.completionTime << " TAT=" << p.turnAroundTime << " WT=" << p.waitTime << " RT=" << p.responseTime;
        return outputStream;
    }

} ; 

#endif
