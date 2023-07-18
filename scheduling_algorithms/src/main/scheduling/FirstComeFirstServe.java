package scheduling;

import process.Process; 
import java.util.ArrayList;

public class FirstComeFirstServe extends Scheduler {

    @Override
    public void setReadyQueue( ArrayList<Process> processes ) {
        this.processes = processes ; 
    }

    @Override
    public void schedule() {
        // First come, first out
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
