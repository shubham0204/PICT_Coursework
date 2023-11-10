from collections import deque

def first_in_first_out( page_refs , maxlen=3 ):
    memory_frames = deque( maxlen=maxlen )
    hits = 0

    for i , ref in enumerate( page_refs ):

        if ref not in memory_frames:
            if len( memory_frames ) == maxlen:
                memory_frames.popleft()
            memory_frames.append( ref )
            print( "MISS " + str(list(memory_frames)) )
        else:
            hits += 1
            print( "HIT  " + str(list(memory_frames)) )

    return hits , len( page_refs ) - hits


def least_recently_used( page_refs , maxlen=3 ):
    memory_frames = []
    hits = 0
    ref_ages = dict( [ ( ref , 0 ) for ref in page_refs ] )

    for ref in page_refs:

        # Increment the age of page
        # references in memory
        for mem_ref in memory_frames:
            ref_ages[ mem_ref ] += 1

        if not ref in memory_frames:
            # Page fault occurs

            # Determine reference with maximum age
            # in ref_ages
            if len( memory_frames ) == maxlen:
                lru_ref_index = 0
                lru_ref = memory_frames[ lru_ref_index ]
                lru_ref_time = ref_ages[ memory_frames[ lru_ref_index ] ] 
                for i , mem_ref in enumerate(memory_frames):
                    if ref_ages[ mem_ref ] > lru_ref_time:
                        lru_ref = mem_ref
                        lru_ref_time = ref_ages[ mem_ref ]
                        lru_ref_index = i
                memory_frames[ lru_ref_index ] = ref
                ref_ages[ lru_ref ] = 0
            else:
                memory_frames.append( ref )
                ref_ages[ ref ] = 0
            print( "MISS " + str(ref) + " " + str(memory_frames) )

        else:
            ref_ages[ ref ] = 0
            hits += 1
            print( "HIT  " + str(ref) + " "  + str(memory_frames) )

    return hits , len( page_refs ) - hits


def optimal( page_refs , maxlen=3 ):
    memory_frames = []
    hits = 0

    for i , ref in enumerate( page_refs ):

        if not ref in memory_frames:
            # Page fault occurs

            if len( memory_frames ) == maxlen:
                max_usage_index = 0
                max_usage = 0
                for p in range( len( memory_frames ) ):
                    for j in range( i + 1 , len( page_refs ) ):
                        if page_refs[ j ] == memory_frames[ p ]:
                            if j - i > max_usage:
                                max_usage = j - i
                                max_usage_index = p
                            break
                    else:
                        max_usage_index = p
                        break
                memory_frames[ max_usage_index ] = ref

            else:
                memory_frames.append( ref )
            print( "MISS " + str(ref) + " " + str(memory_frames) )

        else:
            hits += 1
            print( "HIT  " + str(ref) + " "  + str(memory_frames) )

    return hits , len( page_refs ) - hits



refs = [ 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 ]
hits , misses = first_in_first_out( refs , maxlen=3 ) 
print( hits , misses )

refs = [ 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 ]
hits , misses = least_recently_used( refs , maxlen=3 ) 
print( hits , misses )

refs = [ 1 , 3 , 0 , 3 , 5 , 6 , 3 , 4 , 7 , 1 , 0 , 8 ]
hits , misses = optimal( refs , maxlen=3 ) 
print( hits , misses )