# N-queens as a CSP (Constraint Satisfaction Problem)
# and solving it with branch-and-bound method
# References: 
# https://www.cs.toronto.edu/~fbacchus/Presentations/CSP-BasicIntro.pdf
# https://www.cs.auckland.ac.nz/courses/compsci369s1c/lectures/GG-notes/CS369-Backtrack-BB.pdf

N = 4

# Initial configuration
config = [ 0 for _ in range(N) ]

def validate_config(
    config: list[int]
) -> bool:
    for i in range( N ):
        for j in range( N ):
            if config[i] == config[j] == -1:
                continue
            if (config[i] == config[j]) or (abs( i - j ) != abs( config[i] - config[j] )):
                return False
    return True