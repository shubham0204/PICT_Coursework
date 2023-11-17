from collections import deque
from process import Process

class FirstComeFirstServe:

    @classmethod
    def schedule( cls , processes: list[Process] ):
        ready_queue = deque()
        schedule: list[Process] = []
        time: int = 0
        curr_proc: Process = None
        n_completed_proc : int = 0 
        is_proc_exec: bool = False

        while n_completed_proc < len( processes ):

            for proc in processes:
                if proc.at == time:
                    ready_queue.append( proc )

            if is_proc_exec and time == (curr_proc.rt + curr_proc.bt):
                # curr_proc execution completed, calculate parameters
                # and add it to schedule
                curr_proc.ct = time
                curr_proc.rt -= curr_proc.at
                curr_proc.calc_params()
                schedule.append( curr_proc )
                n_completed_proc += 1
                is_proc_exec = False

            if not is_proc_exec and len( ready_queue ) > 0:
                # Start execution of first process from 
                # ready queue
                curr_proc = ready_queue.popleft()
                curr_proc.rt = time
                is_proc_exec = True

            time += 1

        avg_tat = sum( [ proc.tat for proc in schedule ] ) / len( processes )
        avg_wt = sum( [ proc.wt for proc in schedule ] ) / len( processes )
        print( f"AVG TAT: {avg_tat}" )
        print( f"AVG WT: {avg_wt}" )
        for proc in schedule:
            print( proc )

bts : list[int] = [ 3 , 6 , 1 , 2 , 4 ] 
ats : list[int] = [ 0 , 1 , 3 , 2 , 4 ]
processes: list[Process] = []
for i , ( at , bt ) in enumerate( zip( ats , bts ) ):
    proc = Process()
    proc.id = i + 1
    proc.at = at
    proc.bt = bt
    processes.append( proc )

FirstComeFirstServe.schedule( processes )


