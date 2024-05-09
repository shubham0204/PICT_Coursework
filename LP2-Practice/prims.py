
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
        
    def print( self ):
        for ( node , neighbors ) in self.adjacency_list.items():
            print( node , end=" : " )
            for n in neighbors:
                print( n , end=" " )
            print()

        
def min_spanning_tree( graph ):
    start_node = list(graph.adjacency_list.keys())[0]
    mst_cost = 0
    num_mst_edges = 1
    num_graph_nodes = len(graph.adjacency_list)
    visited = [ start_node ]
    mst = Graph()
    while num_mst_edges <= num_graph_nodes - 1:
        min_weight_edge = None
        min_weight = 1e10
        for v in visited:
            edge = min(
                [ 
                    neighbor 
                    for neighbor in graph.adjacency_list[v] 
                    if neighbor[0] not in visited
                ] , 
                key = lambda neighbor: neighbor[1] , 
                default = None
            )
            if edge is None:
                continue
            if edge[1] < min_weight:
                min_weight = edge[1]
                min_weight_edge = ( v , edge[0] , edge[1] )
        print( f"Edge added: {min_weight_edge[0]} - {min_weight_edge[1]} , weight = {min_weight_edge[2]}")
        mst.add_edge(min_weight_edge[0], min_weight_edge[1], min_weight_edge[2])
        mst_cost += min_weight_edge[2]
        visited.append( min_weight_edge[1] )
        num_mst_edges += 1
    print( f"MST cost: {mst_cost}" )
    mst.print()

graph = Graph()
graph.add_edge("a", "b", 1)
graph.add_edge("b", "c", 2)
graph.add_edge("c", "d", 5)
graph.add_edge("d", "a", 4)
graph.add_edge("a", "c", 3)
graph.print()

min_spanning_tree(graph)

