import subprocess

def run( command : str ) -> str:
    p = subprocess.Popen( command , stdout=subprocess.PIPE , shell=True )
    while True:
        line = p.stdout.readline().decode( "utf-8" )
        if not line:
            break
        else:
            yield line

ip_addr = input( "Enter IP address of remote machine: " )
