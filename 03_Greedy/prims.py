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

    def check_cycle(self, src: str, dst: str) -> bool:
        if src not in self.adj_list or dst not in self.adj_list:
            return False
        queue = [src]
        visited = [src]
        while len(queue) != 0:
            front = queue[0]
            del queue[0]
            if front == dst:
                return True
            neighbors = self.adj_list[front]
            for neighbor in neighbors:
                if neighbor[0] not in visited:
                    visited.append(neighbor[0])
                    queue.append(neighbor[0])
        return False

    def __str__(self) -> str:
        str_repr = ""
        for key, val in self.adj_list.items():
            str_repr += f"{key} {self.adj_list[key]}\n"
        return str_repr


def min_spanning_tree(graph: Graph):
    curr_node = list(graph.adj_list.keys())[0]
    graph_num_nodes = len(graph.adj_list)
    tree_num_edges = 1
    min_cost = 0
    visited: list[str] = [curr_node]
    spanning_tree: Graph = Graph()
    while tree_num_edges < graph_num_nodes - 1:
        min_weight_edge = min(
            [
                neighbor
                for neighbor in graph.adj_list[curr_node]
                if neighbor[0] not in visited
            ],
            key=lambda x: x[1],
            default=None,
        )
        if min_weight_edge is None:
            continue
        spanning_tree.add_edge(curr_node, min_weight_edge[0], min_weight_edge[1])
        min_cost += min_weight_edge[1]
        curr_node = min_weight_edge[0]
        tree_num_edges += 1
        visited.append(min_weight_edge[0])
    print(f"Min cost of spanning tree {min_cost}")


graph = Graph()

while True:
    print("Add edge to the graph: ")
    node_a = input("Enter first node: ")
    node_b = input("Enter second node: ")
    if node_a == node_b == "-":
        break
    weight = int(input("Enter weight of the edge: "))
    graph.add_edge(node_a, node_b, weight)

print("Graph adjacency list: ")
print(graph)

min_spanning_tree(graph)
