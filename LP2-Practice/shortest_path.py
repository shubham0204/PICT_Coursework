import pprint
class Graph:

    def __init__( self ):
        self.adjacency_list = {}

    def add_edge( self , node_a , node_b , weight ):
        if node_a in self.adjacency_list:
            self.adjacency_list[ node_a ].append( (node_b , weight) )
        else:
            self.adjacency_list[ node_a ] = [ (node_b , weight) ]
        if node_b in self.adjacency_list:
            self.adjacency_list[ node_b ].append( (node_a , weight) )
        else:
            self.adjacency_list[ node_b ] = [ (node_a , weight) ]

    def get_edge( self , node_a , node_b ):
        for n in self.adjacency_list[ node_a ]:
            if n[0] == node_b:
                return n[1]
        
    def print( self ):
        for ( node , neighbors ) in self.adjacency_list.items():
            print( node , end=" : " )
            for n in neighbors:
                print( n , end=" " )
            print()

def single_source_shortest_path( graph , src ):
    Q = []
    dist = {}
    prev = {}
    for node in graph.adjacency_list.keys():
        dist[node] = 1e10
        prev[node] = None
        Q.append( node )
    dist[src] = 0

    while len(Q) != 0:
        min_dist_node = min( [ n for n in Q ] , key = lambda n: dist[n] )
        Q.remove( min_dist_node )
        min_dist_node_neighbors = [ neighbor[0] 
                        for neighbor in graph.adjacency_list[ min_dist_node ]
                        if neighbor[0] in Q ]
        for n in min_dist_node_neighbors:
            alt = dist[min_dist_node] + graph.get_edge(min_dist_node , n)
            if alt < dist[n]:
                dist[n] = alt
                prev[n] = min_dist_node

    for node in prev.keys():
        path = [ node ]
        path_node = prev[node]
        while path_node is not None:
            path.append( path_node )
            path_node = prev[path_node]
        print( f"Path for {node} is {path}" )

        
    pprint.pprint( dist )
    pprint.pprint( prev )

graph = Graph()
graph.add_edge("0", "1", 2)
graph.add_edge("0", "2", 6)
graph.add_edge("2", "3", 8)
graph.add_edge("1", "3", 5)
graph.add_edge("3", "4", 10)
graph.add_edge("3", "5", 15)
graph.add_edge("4", "6", 2)
graph.add_edge("5", "6", 6)
single_source_shortest_path(graph, "0")
        