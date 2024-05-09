
class Graph:

    def __init__( self ):
        self.adjacency_list = {}

    def add_edge( self , node_a , node_b ):
        if node_a in self.adjacency_list:
            self.adjacency_list[ node_a ].append( node_b )
        else:
            self.adjacency_list[ node_a ] = [ node_b ]
        if node_b in self.adjacency_list:
            self.adjacency_list[ node_b ].append( node_a )
        else:
            self.adjacency_list[ node_b ] = [ node_a ]

    def print( self ):
        for ( node , neighbors ) in self.adjacency_list.items():
            print( node , end=" : " )
            for n in neighbors:
                print( n , end=" " )
            print()

    def dfs( self , src , key ):
        visited = []
        return self.dfs_impl(src, key, visited, 0)

    def dfs_impl( self , node , key , visited , level ):
        print( f"[DFS] Visited node {node} at level {level}" )
        if node == key:
            return True
        visited.append( node )
        neighbors = self.adjacency_list[ node ]
        for n in neighbors:
            if n not in visited:
                res = self.dfs_impl( n , key , visited , level + 1 )
                if res:
                    return True
        return False

    def bfs( self , src , key ):
        nodes = [ src ]
        levels = [ 0 ]
        visited = []
        return self.bfs_impl(key, visited, nodes, levels)

    def bfs_impl( self , key , visited , nodes , levels ):
        if len( nodes ) == 0:
            return False
        front = nodes.pop(0)
        level = levels.pop(0)
        visited.append( front )
        print( f"[BFS] Visited node {front} at level {level}" )
        if front == key:
            return True
        neighbors = self.adjacency_list[ front ]
        for n in neighbors:
            if n not in visited:
                nodes.append( n )
                levels.append( level + 1 )
        return self.bfs_impl(key, visited, nodes, levels)


graph = Graph()
graph.add_edge("A", "B")
graph.add_edge("B", "C")
graph.add_edge("C", "D")
graph.add_edge("A", "E")

if graph.dfs( "A" , "E" ):
    print( "Node found" )

if graph.bfs( "A" , "D" ):
    print( "Node found" )