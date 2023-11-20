
class Ring:

    def __init__( self , num_processes: int ):
        self.num_processes = num_processes
        self.alive_status = [ True for _ in range( self.num_processes ) ]

    def kill_process( self , id: int ):
        self.alive_status[ id ] = False

    def start_process( self , id: int ):
        self.alive_status[ id ] = True

    def election( self , initiator_id: int ):

        if not self.alive_status[ initiator_id ]:
            print( f"Process {initiator_id} cannot hold election as it is down" ) 
            return 

        start = initiator_id
        ptr = ( start + 1 ) % self.num_processes
        last_alive_process = start
        while ptr != start:
            if self.alive_status[ ptr ]:
                print( f"Process {last_alive_process} sends ELECTION message to process {ptr}" )
                last_alive_process = ptr
            ptr = ( ptr + 1 ) % self.num_processes
            
        print( f"Process {last_alive_process} sends ELECTION message to process {ptr}" )

        bully_process = max( id for id in range( self.num_processes ) if self.alive_status[ id ] )
        print( f"New coordinator is process {bully_process}")
        print( f"process {bully_process} informs everyone that it is the new coordinator" )

algo = Ring( num_processes=5 )
algo.kill_process( 4 )
algo.kill_process( 1 )
algo.election( 0 )