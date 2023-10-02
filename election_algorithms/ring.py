from process import Process
import random

Process.ACTIVE_PROB = float( input( "Enter active process probability: " ) )

def send_message( message: str , sender: Process , receiver: Process ) -> str:
    return receiver.process_message( sender_identifier=sender.identifier , incoming_message=message )

# Initialize a pool of processes and choose a 
# coordinator randomly
process_pool_size = int( input( "Enter process pool size: " ) )
process_pool: list[Process] = []
for i in range( process_pool_size ):
    process_pool.append( Process( i ) )
random.choice( process_pool ).coordinate = True

# Simulate a pool of processes
# where each process is sending messages to some other process
# If one of the processes is a coordinator, and it fails to respond
# an election is held
num_iterations = 100
for _ in range( num_iterations ):
    p1_index = random.randint( 0 , process_pool_size - 1 )
    p2_index = random.randint( 0 , process_pool_size - 1 )

    if p1_index == p2_index:
        continue

    p1 = process_pool[ p1_index ]
    p2 = process_pool[ p2_index ]
    response = send_message( "hello_world" , p1 , p2 )
    print( "{} {} talking...".format( p1 , p2 ) )

    if response == Process.MESSAGE_NOT_OK and p2.coordinate:
        print( "Coordinator {} not responding. Holding election...".format( p2 ) )

        index = process_pool.index( p1 )
        initiator = process_pool[ index ]
        initiator.coordinate = False
    
        process_list = []
        cntr = index + 1
        curr_process = process_pool[ cntr ]
        while curr_process.identifier != initiator.identifier:
            print( "Sent ELECTION message to {}".format( curr_process ) )
            response = send_message( Process.MESSAGE_ELECTION , initiator , curr_process )
            if response == Process.MESSAGE_OK:
                process_list.append( curr_process )
                print( "Positive response from {}. Adding to message list...".format( curr_process ) )
            else:
                print( "Negative response from {}. Skipped.".format( curr_process ) )
            cntr = ( cntr + 1 ) % process_pool_size
            curr_process = process_pool[ cntr ]

        max_identifier_process = max( process_list , key=lambda process: process.identifier )
        max_identifier_process.coordinate = True
        print( "Max identifier process is {}, the new coordinator".format( max_identifier_process ) )