from process import Process
import random

def send_message( message: str , sender: Process , receiver: Process ) -> str:
    return receiver.process_message( sender_identifier=sender.identifier , message=message )

# Initialize a pool of processes and choose a 
# coordinator randomly
process_pool_size = 10
process_pool: list[Process] = []
for i in range( process_pool_size ):
    process_pool.append( Process( i ) )
random.choice( process_pool ).coordinate = True


