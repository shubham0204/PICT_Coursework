package scheduling;

import java.util.ArrayList;
import process.Process;


public class ShortestJobFirst extends Scheduler {

    @Override
    public void setReadyQueue(ArrayList<Process> processes) {
        this.processes = processes;
    }

    @Override
    public void schedule() {
        ArrayList<Process> shortestJobs = this.processes; 
        for( int i = 0 ; i < processes.size() ; i++ ) {
            for( int j = i ; j > 0 ; j-- ) {
                if( shortestJobs.get( j ).getBurstTime() < shortestJobs.get( j - 1 ).getBurstTime() ) {
                    Process temp = shortestJobs.get( j ) ; 
                    shortestJobs.set( j - 1 , shortestJobs.get( j )) ; 
                    shortestJobs.set( j , temp) ; 
                }
            }
        }
        long processWaitTime = 0L;
        scheduledProcesses = new ArrayList<>() ; 
        for( int i = 0 ; i < processes.size() ; i++ ) {
            Process currentProcess = processes.get( i ) ; 
            currentProcess.setWaitTime(processWaitTime);
            currentProcess.setTurnAroundTime(processWaitTime + currentProcess.getBurstTime());
            processWaitTime += currentProcess.getBurstTime() ; 
            scheduledProcesses.add( currentProcess ) ; 
        }
    }

    @Override
    public void printScheduledSequence() {
        for( Process p : scheduledProcesses ) {
            System.out.println( p.toString() );
        }
    }

    @Override
    public float getAverageWaitTime() {
        totalWaitTime = 0L ; 
        for( Process p : scheduledProcesses ) {
            totalWaitTime += p.getWaitTime() ; 
        }
        return (float)totalWaitTime / processes.size() ; 
    }

}
