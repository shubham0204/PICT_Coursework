import indian_names
import random

DOMAINS = [
    "CN" , 
    "ML" , 
    "AppDev" , 
    "ES" , 
    "Others" , 
    "DSP"
]

team_prefixes = [
    "developers" , 
    "programmers" , 
    "bytes" , 
    "problem-solvers" , 
    "pro" , 
    "coders" , 
]

team_suffixes = [
    "herd" , 
    "group" , 
    "hub" , 
    "den" , 
    "house"
]

engineering_institutes = [
    "Indian Institute of Technology Bombay",
    "Visvesvaraya National Institute of Technology Nagpur",
    "College of Engineering Pune",
    "Veermata Jijabai Technological Institute, Mumbai",
    "Walchand College of Engineering, Sangli",
    "Sardar Patel College of Engineering, Mumbai",
    "Government College of Engineering, Aurangabad",
    "Government College of Engineering, Amravati",
    "Dwarkadas J. Sanghvi College of Engineering, Mumbai",
    "Fr. Conceicao Rodrigues College of Engineering, Mumbai",
    "Pillai College of Engineering, New Panvel",
    "Vishwakarma Institute of Technology, Pune",
    "Sinhgad College of Engineering, Pune",
    "KJ Somaiya College of Engineering, Mumbai",
    "Sardar Patel Institute of Technology, Mumbai",
    "Shri Ramdeobaba College of Engineering and Management, Nagpur",
    "Rajiv Gandhi Institute of Technology, Mumbai",
    "Vidyalankar Institute of Technology, Mumbai",
    "Datta Meghe College of Engineering, Navi Mumbai",
    "Pune Institute of Computer Technology"
]

def get_random_institute() -> str:
    return random.choice( engineering_institutes )

def get_random_domain() -> str:
    return random.choice( DOMAINS )

def get_random_team_name() -> str:
    return random.choice( team_prefixes ) + "-" + random.choice( team_suffixes )

def get_random_contact_number() -> str:
    return "9" + "".join( [ str(random.randint( 1 , 9 )) for _ in range(9) ] )

def get_random_name() -> str:
    return indian_names.get_full_name()

def get_random_room() -> str:
    return random.choice( [ "A1" , "A2" , "A3" ] ) + \
           random.choice( [ "1" , "2" , "3" ] ) + "0" + \
           str(random.randint( 1 , 7 ))

def to_sql_string( var: str ) -> str:
    return "'{}'".format( var )

def to_sql_tuple( *args ) -> str:
    arguments = ",".join( args )
    return "(" + arguments + ")"
