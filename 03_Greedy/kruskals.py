class Graph:

    def __init__( self , num_nodes: int ):
        self.num_nodes = num_nodes
        self.adj_list = [ [] for _ in range( self.num_nodes ) ]
        self.edges = []

    def add_edge( self , node_1: int , node_2: int , weight: int  ):
        self.adj_list[ node_1 ].append( (node_2, weight) )
        self.adj_list[ node_2 ].append( (node_1, weight) )
        self.edges.append( ( node_1 , node_2 , weight ) )
        
    def check_cycle( self , src: int , dst: int ) -> bool:
        queue = [ src ]
        visited = [ src ]
        while len( queue ) != 0:
            front = queue[0]
            del queue[0]
            if front == dst:
                return True
            neighbors = self.adj_list[ front ]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append( neighbor[0] )
                    queue.append( neighbor[0] )
        return False
    
    def bfs( self ):
        queue = [ 0 ]
        visited = [ 0 ]
        travel_sequence = []
        while len( queue ) != 0:
            front = queue[0]
            del queue[0]
            travel_sequence.append( front )
            neighbors = self.adj_list[ front ]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append( neighbor[0] )
                    queue.append( neighbor[0] )
        print( travel_sequence )

    def __str__( self ) -> str:
        str_repr = ""
        for i in range( len( self.adj_list ) ):
            str_repr += f"{i} {self.adj_list[i]}\n"
        return str_repr
    
def min_spanning_tree( graph: Graph ):
    ordered_edges = list( sorted( graph.edges , key=lambda edge: edge[2] ) )
    spanning_tree: Graph = Graph( graph.num_nodes )
    min_cost: int = 0
    for edge in ordered_edges:
        if spanning_tree.check_cycle( edge[0] , edge[1] ):
            continue
        spanning_tree.add_edge( *edge )
        min_cost += edge[2]
    print( min_cost )
    spanning_tree.bfs()
    
graph = Graph( 5 )
graph.add_edge( 0 , 1 , 1 )
graph.add_edge( 1 , 2 , 3 )
graph.add_edge( 2 , 3 , 4 )
graph.add_edge( 0 , 2 , 7 )
graph.add_edge( 0 , 3 , 10 )
graph.add_edge( 3 , 4 , 2 )
graph.add_edge( 0 , 4 , 5 )
graph.bfs()

min_spanning_tree( graph )