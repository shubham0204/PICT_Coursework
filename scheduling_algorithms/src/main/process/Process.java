package process ; 

public class Process {

    String name ; 
    long burstTime = 0L ; 
    long waitTime = 0L ; 
    long turnAroundTime = 0L ; 

    public String getName() {
        return this.name ; 
    }

    public void setName( String name ) {
        this.name = name ; 
    }

    public void setBurstTime( long burstTime ) {
        this.burstTime = burstTime ; 
    }

    public long getBurstTime() {
        return this.burstTime ; 
    }

    public void setWaitTime( long waitTime ) {
        this.waitTime = waitTime ; 
    }

    public long getWaitTime() {
        return this.waitTime ; 
    }

    public void setTurnAroundTime( long turnAroundTime ) {
        this.turnAroundTime = turnAroundTime ; 
    }

    public long getTurnAroundTime() {
        return this.turnAroundTime ; 
    }

    @Override
    public String toString() {
        return "[ " + this.name + "\n" +
         "burst_time = " + this.burstTime + "\n" + 
         "wait_time = " + this.waitTime + "\n" + 
         "turn_around_time = " + this.turnAroundTime + "]" ; 
    }

}