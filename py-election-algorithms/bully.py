class Bully:

    def __init__( self , num_processes: int ):
        self.num_processes = num_processes
        self.alive_status: list[True] = [ True for _ in range( num_processes ) ]

    def kill_process( self , id: int ):
        self.alive_status[ id ] = False

    def start_process( self , id: int ):
        self.alive_status[ id ] = True

    def election( self , initiator_id: int ):
        if initiator_id > self.num_processes - 1:
            return

        if not self.alive_status[ initiator_id ]:
            print( f"Process {initiator_id} cannot hold election as it is down. " )
            return

        print( f"Election started by process {initiator_id}" )

        for i in range( initiator_id + 1 , self.num_processes ):
            print( f"ELECTION message sent to process {i} by process {initiator_id}")

        for i in range( initiator_id + 1 , self.num_processes ):
            if self.alive_status[ i ]:
                print( f"Process {i} responded OK to ELECTION" )

        for i in range( initiator_id + 1 , self.num_processes ):
            if self.alive_status[ i ]:
                self.election( i )
                return

        bully_process = max( id for id in range( self.num_processes ) if self.alive_status[ id ] )
        print( f"New coordinator is process {bully_process}")
        print( f"process {bully_process} informs everyone that it is the new coordinator" )

algo = Bully( num_processes=5 )
algo.kill_process( 4 )
algo.kill_process( 1 )
algo.election( 0 )
