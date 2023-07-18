package scheduling;

import java.util.ArrayList;
import process.Process; 

public abstract class Scheduler {

    protected ArrayList<Process> processes; 
    protected ArrayList<Process> scheduledProcesses;
    protected long totalWaitTime = 0L ; 

    abstract public void setReadyQueue( ArrayList<Process> processes ) ;

    abstract public void schedule() ;

    abstract public void printScheduledSequence() ;

    abstract public float getAverageWaitTime() ;


}
