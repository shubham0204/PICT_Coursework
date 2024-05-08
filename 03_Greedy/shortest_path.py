"""
Pseudo-code for determining shortest path to each node
in a graph, from a single source node (Dijkstra's algorithm)
Ref: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode

function Dijkstra(Graph, source):
   
    for each vertex v in Graph.Vertices:
        dist[v] ← INFINITY
        prev[v] ← UNDEFINED
        add v to Q
    dist[source] ← 0
   
    while Q is not empty:
        u ← vertex in Q with minimum dist[u]
        remove u from Q
       
        for each neighbor v of u still in Q:
            alt ← dist[u] + Graph.Edges(u, v)
            if alt < dist[v]:
                dist[v] ← alt
                prev[v] ← u

    return dist[], prev[]
"""
import pprint

class Graph:
    def __init__(self):
        self.adj_list: dict[str, list[(str, int)]] = {}
        self.edges = []

    def add_edge(self, node_1: str, node_2: str, weight: int):
        if node_1 not in self.adj_list:
            self.adj_list[node_1] = []
        self.adj_list[node_1].append((node_2, weight))
        if node_2 not in self.adj_list:
            self.adj_list[node_2] = []
        self.adj_list[node_2].append((node_1, weight))
        self.edges.append((node_1, node_2, weight))

    def get_edge(self , node_1: str, node_2: str) -> int:
        neighbors = self.adj_list[node_1]
        for n in neighbors:
            if n[0] == node_2:
                return n[1]
        return None

    def __str__(self) -> str:
        str_repr = ""
        for key, val in self.adj_list.items():
            str_repr += f"{key} {self.adj_list[key]}\n"
        return str_repr

def single_source_shortest_path( graph: Graph , src: str ) -> dict[str,int]:
    Q: list[str] = []

    dist: dict[str,int] = {} # min distance of each node from src
    prev: dict[str,int] = {} # current min distance of each node from src
    for n in graph.adj_list.keys():
        dist[n] = 1e10      # dist[n] = infinity
        prev[n] = None      # prev[n] = UNDEFINED
        Q.append( n )
    dist[src] = 0

    while len( Q ) != 0:
        u = min( 
            [ (n,dist[n]) for n in Q ] , 
            key=lambda x: x[1] 
        )[0]
        Q.remove( u )
        for v in [ neighbor[0] for neighbor in graph.adj_list[u] if neighbor[0] in Q ]:
            alt = dist[u] + graph.get_edge(u, v)
            if alt < dist[v]:
                dist[v] = alt
                prev[v] = u
    for node in prev.keys():
        path = [ node ]
        path_node = prev[node]
        while path_node is not None:
            path.append( path_node )
            path_node = prev[path_node]
        print( f"Path for {node} is {path}" )
    return dist , prev

graph = Graph()

while True:
    print("Add edge to the graph: ")
    node_a = input("Enter first node: ")
    node_b = input("Enter second node: ")
    if node_a == node_b == "-":
        break
    weight = int(input("Enter weight of the edge: "))
    graph.add_edge(node_a, node_b, weight)

src = input( "Enter src node: " )

print("Graph adjacency list: ")
print(graph)
dists , paths = single_source_shortest_path(graph, src)
print( f"Distance of all nodes from source node {src}" )
pprint.pprint( dists )
print( f"Shortest paths of all nodes from source node {src}" )
pprint.pprint( paths )

"""
graph = Graph()
graph.add_edge("a", "b", 2)
graph.add_edge("b", "d", 5)
graph.add_edge("a", "c", 5)
graph.add_edge("c", "d", 8)
graph.add_edge("a", "d", 9)
print( graph )
dists , paths = single_source_shortest_path(graph, "a")
print( dists )
print( paths )
"""