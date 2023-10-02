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

        # Hold election
        # 1. Send ELECTION messages to all higher processes
        # 2. If any one of them responds with OK, select that process as coordinator

        higher_processes = process_pool[ p1_index + 1 : ]
        for process in higher_processes:
            print( "Sent ELECTION message to {}".format( process ) ) 
            response = send_message( Process.MESSAGE_ELECTION , p2 , process )
            if response == Process.MESSAGE_OK:
                print( "New coordinator chosen as {}".format( process ) ) 
                process.coordinate = True
                break
            else:
                print( "Negative response from {}".format( process ) )
                
        p2.coordinate = False