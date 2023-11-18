from collections import deque
from process import Process

class PriorityScheduling:

    @classmethod
    def schedule( cls , processes: list[Process] ):
        
        ready_queue = deque()
        schedule: list[Process] = []

        curr_proc: Process = None
        is_proc_exec: bool = False
        time: int = 0
        n_completed_proc: int = 0

        while n_completed_proc < len( processes ):

            for proc in processes:
                if proc.at == time:
                    ready_queue.append( proc )

            if is_proc_exec and curr_proc.rt + curr_proc.bt == time:
                # Process execution completed
                curr_proc.rt -= curr_proc.at
                curr_proc.ct = time
                curr_proc.calc_params()
                n_completed_proc += 1
                is_proc_exec = False
                schedule.append( curr_proc )

            if not is_proc_exec and len( ready_queue ) > 0:
                # Schedule the process with highest priority
                # Lower the number, higher is the priority
                curr_proc = min( ready_queue , key= lambda proc: proc.priority )
                ready_queue.remove( curr_proc )
                curr_proc.rt = time
                is_proc_exec = True

            time += 1

        avg_tat = sum( [ proc.tat for proc in schedule ] ) / len( processes )
        avg_wt = sum( [ proc.wt for proc in schedule ] ) / len( processes )
        print( f"AVG TAT: {avg_tat}" )
        print( f"AVG WT: {avg_wt}" )
        for proc in schedule:
            print( proc )


bts : list[int] = [ 11 , 28 , 2 , 10 , 16  ] 
ats : list[int] = [ 0 , 5 , 12  , 2 , 9  ]
pts : list[int] = [ 2 , 0 , 3 , 1 , 4 ]
processes: list[Process] = []
for i , ( at , bt , pt ) in enumerate( zip( ats , bts , pts ) ):
    proc = Process()
    proc.id = i + 1
    proc.priority = pt
    proc.at = at
    proc.bt = bt
    processes.append( proc )

PriorityScheduling.schedule( processes )

