from collections import deque

class Proces:

    def __init__():
        self.name = None
        self.arrival_time = 0
        self.burst_time = 0
        self.completion_time = 0
        self.turn_around_time = 0
        self.wait_time = 0
        self.response_time = 0
    
    def __str__() -> str:
        return "process {}".format( name )


class FirstComeFirstServe:

    def schedule( processes: list[Process] ):
        ready_queue = deque()
        output = list()

        time = 0
        is_executing = False
        current_process = processes[0]
        n = 0

        while n < len( processes ):

            for process in processes:
                if process.arrival_time == time:
                    ready_queue.append( process )

            if time == (current_process.arrival_time + current_process.burst_time):
                is_executing = False
                current_process.response_time -= current_process.arrival_time
                current_process.completion_time = time
                current_process.turn_around_time = current_process.completion_time - current_process.arrival_time
                current_process.wait_time = current_process.turn_around_time - current_process.burst_time
                output.append( current_process )
                n += 1

            if not is_executing and len( ready_queue ) != 0:
                current_process = ready_queue.pop()
                current_process.response_time = time
                is_executing = True

            time += 1

        avg_tat = 0
        avg_wt = 0
        for process in output:
            avg_tat += process.turn_around_time
            avg_wt += process.wait_time
            print( process )
        print( "Average TAT = " , avg_tat / len( output ) )
        print( "Average WT = " , avg_wt / len( output ) )


class RoundRobin:

    def schedule( processes: list[Process] , quantum: int ):

        burst_times: dict[str,int] = {}
        for process in processes:
            burst_times[ process.name ] = process.burst_time

        ready_queue: list[Process] = []
        output: list[Process] = []
        current_process = processes[0]

        time = 0 
        is_executing = False
        n = 0
        step = 0
        current_process_remaining_bt = 0

        while n < processes.size():

            for process in processes:
                if process.arrival_time == time:
                    ready_queue.append( process )

            if current_process_remaining_bt == 0:
                # TODO: Calculate process parameters
                n += 1
                output.append( current_process )
                is_executing = False

                if len( ready_queue ) != 0:
                    current_process = ready_queue[0]
                    if current_process.response_time == 0:
                        current_process.response_time = time
                    current_process_remaining_bt = current_process.burst_time
                    ready_queue.pop( 0 )
                    step = time + quantum
                    is_executing = True

            if is_executing:
                if time == step:
                    current_process.burst_time = current_process_remaining_bt
                    ready_queue.append( current_process )

                    if len( ready_queue ) != 0:
                        current_process = ready_queue[0]
                        if current_process.response_time == 0:
                            current_process.response_time = time
                        current_process_remaining_bt = current_process.burst_time
                        ready_queue.pop( 0 )
                        step = time + quantum
                        is_executing = True
            else:
                if len( ready_queue ) != 0:
                    current_process = ready_queue[0]
                    current_process_remaining_bt = current_process.burst_time
                    ready_queue.pop( 0 )
                    step = time + quantum
                    is_executing = True
                
            if is_executing:
                current_process_remaining_bt -= 1

            time += 1
            
