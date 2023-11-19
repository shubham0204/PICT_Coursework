from collections import deque

# refs -> page references
# memory_size -> max. number of pages that can be accomodated in the memory
# memory -> buffer in which pages are stored

def first_in_first_out( refs: list[int] , memory_size: int ):
    memory = deque()
    hits: int = 0
    for ref in refs:
        if ref not in memory:
            # Page fault occurs
            # swap out leftmost page and swap in `ref` if memory is full
            if len( memory ) == memory_size:
                memory.popleft()
            memory.append( ref )
        else:
            hits += 1
        print( ref , list(memory) ) 
    misses: int = len( refs ) - hits
    return hits , misses

def least_recently_used( refs: list[int] , memory_size: int ):
    memory: list[int] = []
    hits: int = 0 
    for ref_index , ref in enumerate(refs):
        if ref not in memory:
            # Page fault occurs
            # swap out least recently accessed page and swap in `ref` if memory is full
            if len( memory ) == memory_size:
                # Iterate through each page in memory
                # and check which one was least recently accessed
                access_gaps: list[int] = [ refs[ ref_index - 1 :: -1 ].index(memory_ref) for memory_ref in memory]
                lru_frame_index = access_gaps.index( max( access_gaps ) )
                memory[ lru_frame_index ] = ref
            else:
                memory.append( ref )
        else:
            hits += 1
        print( ref , list(memory) ) 
    misses: int = len( refs ) - hits
    return hits , misses

def optimal( refs: list[int] , memory_size: int ):
    memory: list[int] = []
    hits: int = 0 
    for ref_index , ref in enumerate(refs):
        if ref not in memory:
            # Page fault occurs
            # swap out page farthest away in the refs
            if len( memory ) == memory_size:
                access_gaps: list[int] = []
                # Iterate through each page in memory
                # and check which one was least recently accessed
                for memory_ref in memory:
                    try:
                        access_gaps.append( refs[ ref_index + 1 : ].index( memory_ref ) - (ref_index+1) )
                    except:
                        access_gaps.append( 1e+3 ) 
                max_gap_index = access_gaps.index( max( access_gaps ) )
                memory[ max_gap_index ] = ref
            else:
                memory.append( ref )
        else:
            hits += 1
        print( ref , list(memory) ) 
    misses: int = len( refs ) - hits
    return hits , misses


refs = [ 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 ]
hits , misses = first_in_first_out( refs , memory_size=3 ) 
print( hits , misses )

refs = [ 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 ]
hits , misses = least_recently_used( refs , memory_size=3 ) 
print( hits , misses )

refs = [ 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 ]
hits , misses = optimal( refs , memory_size=3 ) 
print( hits , misses )
