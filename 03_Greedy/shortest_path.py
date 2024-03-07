
class Graph:

    def __init__( self , num_nodes: int ):
        self.num_nodes = num_nodes
        self.adj_list = [ [] for _ in range( self.num_nodes ) ]

    def add_edge( self , node_1: int , node_2: int , weight: int ):
        self.adj_list[ node_1 ].append( (node_2 , weight) )
        self.adj_list[ node_2 ].append( (node_1 , weight) )

    def __str__( self ) -> str:
        str_repr = ""
        for i in range( len( self.adj_list ) ):
            str_repr += f"{i} {self.adj_list[i]}\n"
        return str_repr

    def shortest_path( self , src_node: int ):
        assert( src_node < num_nodes , "Invalid node" )
        