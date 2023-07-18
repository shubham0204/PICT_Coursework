
import java.util.ArrayList;

import process.Process ; 
import scheduling.FirstComeFirstServe;  
import scheduling.ShortestJobFirst;

class Main {

    public static void main( String[] args ) {

        long[] burstTimes = { 300 , 125 , 400 , 150 , 100 } ; 
        ArrayList<Process> processes = new ArrayList<>() ; 
        for( int i = 0 ; i < 5 ; i++ ) {
            Process p = new Process() ; 
            p.setName( "P" + (i+1) );
            p.setBurstTime( burstTimes[i] );
            processes.add( p );
        }

        System.out.println( "FCFS" ) ;
        FirstComeFirstServe scheduler = new FirstComeFirstServe() ; 
        scheduler.setReadyQueue( processes );
        scheduler.schedule();
        scheduler.printScheduledSequence();
        System.out.println( "Avg wait time: " + scheduler.getAverageWaitTime() );

    }

}