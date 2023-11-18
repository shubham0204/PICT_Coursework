from process import Process
from collections import deque

class RoundRobin:

    @classmethod
    def schedule( cls , processes: list[Process] , quantum: int ):

        burst_times: dict[int,int] = {}
        for proc in processes:
            burst_times[ proc.id ] = proc.bt

        ready_queue = deque()
        schedule: list[Process] = []
        is_proc_exec: bool = False
        curr_proc: Process = None
        curr_proc_bt: int = None
        n_completed_proc: int = 0
        step: int = None
        time: int = 0

        while n_completed_proc < len( processes ):

            # 1. Add processes to ready_queue if any has arrived
            for proc in processes:
                if proc.at == time:
                    ready_queue.append( proc )

            # 2. Check for completion of current process
            if is_proc_exec and curr_proc_bt == 0:
                curr_proc.ct = time
                curr_proc.bt = burst_times[ curr_proc.id ]
                curr_proc.calc_params()
                n_completed_proc += 1
                schedule.append( curr_proc )
                is_proc_exec = False

            # 3. Check if current process can be preempted
            if is_proc_exec and time == step:
                # Preempt curr_process
                curr_proc.bt = curr_proc_bt
                ready_queue.append( curr_proc )
                is_proc_exec = False

            # 4. Schedule a process from ready_queue if CPU is idle
            if not is_proc_exec and len( ready_queue ) > 0:
                # Schedule new process from ready_queue
                curr_proc = ready_queue.popleft()
                curr_proc.rt = time
                curr_proc_bt = curr_proc.bt
                step = time + quantum
                is_proc_exec = True

            if is_proc_exec:
                curr_proc_bt -= 1

            time += 1

        avg_tat = sum( [ proc.tat for proc in schedule ] ) / len( processes )
        avg_wt = sum( [ proc.wt for proc in schedule ] ) / len( processes )
        print( f"AVG TAT: {avg_tat}" )
        print( f"AVG WT: {avg_wt}" )
        for proc in schedule:
            print( proc )


bts : list[int] = [ 5 , 4 , 2 , 1 ] 
ats : list[int] = [ 0 , 1 , 2 , 4 ]
processes: list[Process] = []
for i , ( at , bt ) in enumerate( zip( ats , bts ) ):
    proc = Process()
    proc.id = i + 1
    proc.at = at
    proc.bt = bt
    processes.append( proc )

RoundRobin.schedule( processes , 2 )




