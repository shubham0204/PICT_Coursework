import math
import subprocess

def decimal_to_binary( x: int ) -> list[int]:
    p = x
    output: list[int] = []
    while p != 0:
        m = p // 2
        output.append( p % 2 )
        p = m
    if len( output ) < 8:
        output += [ 0 for _ in range( 8 - len( output ) ) ]
    return output[::-1]

def binary_to_decimal( num: list[int] ) -> int:
    output = 0
    for i in range( len( num ) - 1 , -1 , -1 ):
        output += 2**( len(num) - 1 - i ) * num[i]
    return output

def binary_to_str( bin_num: list[int] ) -> str:
    return "".join( [ str(x) for x in bin_num ] )

def boolean_and( num_1: list[int] , num_2: list[int] ) -> list[str]:
    output = []
    for i in range( len( num_1 ) ):
        output.append( int( num_1[i] == 1 and num_2[i] == 1 ) )
    return output

def generate_mask_from_cidr( cidr_num: int ) -> list[int]:
    output = [ 1 for _ in range( cidr_num ) ] 
    if len( output ) < 32:
        output += [ 0 for _ in range( 32 - len( output ) ) ]
    return output

def bin_ip_to_decimal_str( ip_bin: list[int] ) -> str:
    output = ""
    for i in range( 0 , len(ip_bin) , 8 ):
            output += str(binary_to_decimal( ip_bin[i:i+8] )) + "."
    return output[:-1]

def bin_ip_to_octets( ip_bin: list[int] ) -> list[int]:
    output = []
    for i in range( 0 , len(ip_bin) , 8 ):
            output.append( binary_to_decimal( ip_bin[i:i+8] ))
    return output

def iterate_over_subnet( starting_ip_octets: list[int] , n: int ) -> list[tuple[int,int,int,int]]:
    c0 = starting_ip_octets[3]
    c1 = starting_ip_octets[2]
    c2 = starting_ip_octets[1]
    c3 = starting_ip_octets[0]
    i = 0
    output = []
    for c3 in range( starting_ip_octets[0] , 256 ):
        for c2 in range( starting_ip_octets[1] , 256 ):
            for c1 in range( starting_ip_octets[2] , 256 ):
                for c0 in range( starting_ip_octets[3] , 256 ):
                    if i >= n:
                        break
                    output.append( ( c3 , c2 , c1 , c0 ) ) 
                    i += 1
    return output

def run( command : str ) -> str:
    p = subprocess.Popen( command , stdout=subprocess.PIPE , shell=True )
    while True:
        line = p.stdout.readline().decode( "utf-8" )
        if not line:
            break
        else:
            yield line


input_ip_str = input( "Enter an IPv4 address: " ) 
octets = list(map( int , input_ip_str.split( "." )))
ip_bin = []
ip_class = ""
for octet in octets:
    ip_bin += decimal_to_binary( octet ) 
if octets[0] >= 0 and octets[0] <= 126:
    ip_class = "A"
    print( "Class of given IP: Class A" )
    print( "Default subnet mask: 255.0.0.0" )
elif octets[0] >= 128 and octets[0] <= 191:
    ip_class = "B"
    print( "Class of given IP: Class B" )
    print( "Default subnet mask: 255.255.0.0" )
elif octets[0] >= 192 and octets[0] <= 223:
    ip_class = "C"
    print( "Class of given IP: Class C" )
    print( "Default subnet mask: 255.255.255.0" )
elif octets[0] >= 224 and octets[0] <= 239:
    print( "Class of given IP: Class D" )
elif octets[0] >= 240 and octets[0] <= 254:
    print( "Class of given IP: Class E" )

while True:
    print("""
        Options: 
        1. CIDR Number (ex. 27)
        2. Number of subnets (ex. 8)
        """)
    option = int( input( "Enter option: " ) )
    if option == 1:
        cidr_num = int( input( "Enter CIDR Number: ") )
        subnet_mask = generate_mask_from_cidr( cidr_num ) 
        result = boolean_and( ip_bin , subnet_mask )

        num_hosts = 2**(32-cidr_num)
        print( "Number of hosts available: " , num_hosts )
        print( "Subnet mask: " , bin_ip_to_decimal_str( subnet_mask ) , "/" , cidr_num )
        print( "Starting address of subnet: " , bin_ip_to_decimal_str( result ) )
        result_octets = bin_ip_to_octets( result )
        ip_addresses = iterate_over_subnet( result_octets , num_hosts )
        print( "Network address: " , ip_addresses[0] )
        print( "Broadcast address: " , ip_addresses[-1] ) 

    elif option == 2:

        num_subnets = int( input( "Enter number of subnets: " ) )
        num_hosts_per_class = {
            "A": 256 * 256 * 256 , 
            "B": 256 * 256 , 
            "C": 256
        }
        num_hosts_per_subnet = num_hosts_per_class[ ip_class ] // num_subnets
        num_host_bits = int( math.log2( num_hosts_per_subnet ) )
        num_network_bits = 32 - num_host_bits
        subnet_mask = generate_mask_from_cidr( num_network_bits )
        print( "Maximum hosts possible in this IP class: " , num_hosts_per_class[ ip_class ] )
        print( "Number of hosts per subnet (all): " , num_hosts_per_subnet ) 
        print( "Number of hosts per subnet (usable): " , num_hosts_per_subnet - 2 ) 
        print( "Subnet mask required: " , bin_ip_to_decimal_str( subnet_mask ) , "/" , num_network_bits )

        result = boolean_and( ip_bin , subnet_mask )
        result_octets = bin_ip_to_octets( result )
        ip_addresses = iterate_over_subnet( result_octets , num_hosts_per_subnet * num_subnets )
        print( "Subnet ranges are: " )
        subnets = []
        for i in range( 0 , len(ip_addresses) , num_hosts_per_subnet ):
            print( ip_addresses[i] , " - " , ip_addresses[i+num_hosts_per_subnet-1] ) 
            subnets.append( ip_addresses[ i : i+num_hosts_per_subnet ] )

        while True:
            input_command = input( "Command: " ) 
            output_lines: list[str] = [ line for line in run( input_command ) ]
            print( '\n'.join( output_lines ) )

        """
        while True:
            input_dst_ip_str = input( "Command: " ) 
            dst_ip = tuple(map( int , input_dst_ip_str.split()[1].split( "." )))
            
            if self_ip == dst_ip:
                print( "PING SUCCESS (Both IPs are same)" )
                continue

            for subnet in subnets:
                is_found_1 = self_ip in subnet
                is_found_2 = dst_ip in subnet
                if is_found_1 and is_found_2:
                    print( "PING SUCCESS (Both IPs are in same subnet)" )
                    break
            else:
                print( "PING FAILED (Network is unreachable)" )
        """
        