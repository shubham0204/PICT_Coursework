
class Graph:

    def __init__( self ):
        self.adjacency_list = {}
        self.edges = []

    def add_edge( self , node_a , node_b , weight ):
        if node_a in self.adjacency_list:
            self.adjacency_list[ node_a ].append( (node_b , weight) )
        else:
            self.adjacency_list[ node_a ] = [ (node_b , weight) ]
        if node_b in self.adjacency_list:
            self.adjacency_list[ node_b ].append( (node_a , weight) )
        else:
            self.adjacency_list[ node_b ] = [ (node_a , weight) ]
        self.edges.append( (node_a , node_b , weight) )

    def check_cycle( self , src , dst ):
        if src not in self.adjacency_list or dst not in self.adjacency_list:
            return False
        queue = [ src ]
        visited = []
        while not len(queue) == 0:
            front = queue.pop( 0 )
            visited.append( front )
            if front == dst:
                return True
            neighbors = self.adjacency_list[front]
            for n in neighbors:
                if n[0] not in visited:
                    queue.append( n[0] )
        return False
        
    def print( self ):
        for ( node , neighbors ) in self.adjacency_list.items():
            print( node , end=" : " )
            for n in neighbors:
                print( n , end=" " )
            print()

def min_spanning_tree( graph ):
    sorted_edges = sorted( graph.edges , key = lambda x: x[2] )
    mst = Graph()
    mst_cost = 0
    for edge in sorted_edges:
        if not mst.check_cycle( edge[0], edge[1] ):
            mst.add_edge(edge[0], edge[1], edge[2])
            mst_cost += edge[2]
            print( f"Edge added: {edge[0]} - {edge[1]} , weight = {edge[2]}" )
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